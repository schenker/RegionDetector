#ifndef __RegionDetector_REGION_HPP__
#define __RegionDetector_REGION_HPP__

#include <vector>
#include <cassert>
#include <stddef.h>

#include "IdxHelpers.hpp"

namespace RegionDetector {

	class Region {
	public:
		// the indices of all pixels that belong to this region (not including the subregion's pixels)
		std::vector<unsigned int> pixels;

		// number of pixels belonging to this region, including pixels of child regions
		size_t size = 0;

		// sum of the intensities of all pixels in this region (and subregions)
		unsigned long int intensitySum = 0;

		unsigned int level = -1;

		// minimum and maximum pixel coordinates (bounding box)
		int xMin = -1;
		int yMin = -1;
		int xMax = -1;
		int yMax = -1;

		// points to the parent Region
		Region *parent = nullptr;

		// points to the first child Region
		Region *child = nullptr;

		// points to the next sibling Region
		Region *next = nullptr;

		Region() {}

		explicit Region(unsigned int level) : Region() {
			this->level = level;
		}

		void accumulate(const unsigned int pixel, const unsigned int intensity, const unsigned int width) {

			this->pixels.push_back(pixel);
			size++;

			intensitySum += intensity;

			assert(width > 0);
			const int x = Helpers::idxToX(pixel, width);
			const int y = Helpers::idxToY(pixel, width);

			if (x > xMax) {
				xMax = x;
			}

			if (y > yMax) {
				yMax = y;
			}

			if (x < xMin || xMin == -1) {
				xMin = x;
			}

			if (y < yMin || yMin == -1) {
				yMin = y;
			}
		}

		void merge(Region *other) {
			assert(other);
			assert(other->level != 256);
			assert(other->parent == nullptr);
			assert(other->next == nullptr);

			this->intensitySum += other->intensitySum;

			// insert as first child of other region
			other->next = this->child;
			this->child = other;
			other->parent = this;

			if (other->xMax > xMax) {
				xMax = other->xMax;
			}

			if (other->yMax > yMax) {
				yMax = other->yMax;
			}

			if (other->xMin < xMin || xMin == -1) {
				xMin = other->xMin;
			}

			if (other->yMin < yMin || yMin == -1) {
				yMin = other->yMin;
			}

			size += other->size;
		}

		double getMeanIntensity() const {
			return intensitySum / (double)size;
		}

	};

}
#endif
