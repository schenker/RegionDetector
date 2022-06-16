#ifndef __REGIONDETECTOR_REGIONDETECTOR_HPP__
#define __REGIONDETECTOR_REGIONDETECTOR_HPP__

#include <stdint.h>
#include <vector>

#include "Region.hpp"
#include "IdxHelpers.hpp"

namespace RegionDetector {

	// based on "Linear Time Maximally Stable Extremal Regions" by David Nistér and Henrik Stewénius
	template <class REGION_TYPE, class REGION_ALLOCATOR_TYPE> class RegionDetectorDetector {
		static_assert(std::is_base_of<Region, REGION_TYPE>::value, "REGION_TYPE must derive from RegionDetector::Region");
	private:
		unsigned int getNeighborIdx(const unsigned int currentPixel, const unsigned int  width, const unsigned int height, const unsigned int edge) {

			unsigned int x = Helpers::idxToX(currentPixel, width);
			unsigned int y = Helpers::idxToY(currentPixel, width);

			switch (edge) {
			case 0: // N
				if (y > 0) {
					y--;
				}
				break;
			case 1: // E
				if (x < width - 1) {
					x++;
				}
				break;
			case 2: // S
				if (y < height - 1) {
					y++;
				}
				break;
			case 3: // W
				if (x > 0) {
					x--;
				}
				break;
			}

			return Helpers::xyToIdx(x, y, width);
		}

		void processStack(unsigned int newPixelGreyLevel, std::vector<REGION_TYPE*> &regionStack, REGION_ALLOCATOR_TYPE *regionAllocator) {

			Region *first = regionStack.back();
			regionStack.pop_back();

			do {
				assert(!regionStack.empty());
				if (newPixelGreyLevel < regionStack.back()->level) {

					regionStack.push_back(regionAllocator->new_(newPixelGreyLevel));
					assert(regionStack.back());
					regionStack.back()->merge(first);

					return;
				}

				assert(!regionStack.empty());
				regionStack.back()->merge(first);

			} while (newPixelGreyLevel > regionStack.back()->level);
		}

	public:
		/**
		*  @param pixels an uint8_t array of size width*height
		*  @param width the width of the image
		*  @param height the height of the image
		*/
		REGION_TYPE* detect(uint8_t const * const pixels, const unsigned int width, const unsigned int height, REGION_ALLOCATOR_TYPE *regionAllocator) {

			// pixel index first, edge second
			typedef std::pair<unsigned int, unsigned char> PixelAndEdgeType;

			if (width == 0 || height == 0) {
				return nullptr;
			}

			const int N_NEIGHBORS = 4;

			// true if the pixel has already been accessed
			bool * const accessible = new bool[width*height];
			assert(accessible);
			for (unsigned int i = 0; i < width*height; i++) {
				accessible[i] = false;
			}

			std::vector<REGION_TYPE*> componentStack;
			componentStack.reserve(256);

			std::vector<PixelAndEdgeType> boundaryPixels[256];

			unsigned int currentIdx = 0;
			unsigned int currentLevel = pixels[currentIdx];

			accessible[currentIdx] = true;
			REGION_TYPE rootRegion(256);
			componentStack.push_back(&rootRegion);

			unsigned char currentEdge = 0;

		push_empty_component:
			componentStack.push_back(regionAllocator->new_(currentLevel));
			assert(componentStack.back() != nullptr);
		check_neighbors:
			for (; currentEdge < N_NEIGHBORS; currentEdge++) {
				const unsigned int neighborIdx = getNeighborIdx(currentIdx, width, height, currentEdge);
				assert(neighborIdx < width*height);
				if (!accessible[neighborIdx]) {
					accessible[neighborIdx] = true;
					unsigned int neighborLevel = pixels[neighborIdx];
					if (neighborLevel < currentLevel) {
						// neighbor is smaller, push this pixel back
						boundaryPixels[currentLevel].push_back(PixelAndEdgeType(currentIdx, currentEdge + 1));
						currentIdx = neighborIdx;
						currentLevel = neighborLevel;
						currentEdge = 0;
						goto push_empty_component;
					}
					else
					{
						boundaryPixels[neighborLevel].push_back(PixelAndEdgeType(neighborIdx, 0));
					}
				}
			}

			assert(!componentStack.empty());
			auto comp = componentStack.back();
			comp->accumulate(currentIdx, pixels[currentIdx], width);
			const unsigned int previousLevel = currentLevel;

			while (boundaryPixels[currentLevel].empty()) {
				currentLevel++;

				if (currentLevel > 255) {
					assert(componentStack.size() == 2);
					goto done;
				}
			}

			{
				PixelAndEdgeType pe = boundaryPixels[currentLevel].back();
				currentIdx = pe.first;
				currentEdge = pe.second;
			}
			boundaryPixels[currentLevel].pop_back();

			currentLevel = pixels[currentIdx];

			{
				unsigned int newPixelGrayLevel = pixels[currentIdx];

				if (currentLevel != previousLevel) {
					assert(currentLevel > previousLevel);
					currentLevel = newPixelGrayLevel;
					processStack(newPixelGrayLevel, componentStack, regionAllocator);
				}
			}
			goto check_neighbors;


		done:
			// all pixels must be accessible in the end
			for (unsigned int i = 0; i < width*height; i++) {
				assert(accessible[i] == true);
			}

			delete[] accessible;
			return componentStack.back();
		}
	};

}
#endif
