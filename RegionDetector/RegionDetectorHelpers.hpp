#ifndef __REGIONDETECTOR_HELPERS_HPP__
#define __REGIONDETECTOR_HELPERS_HPP__

#include "Region.hpp"
#include <cmath>

namespace RegionDetector {
	namespace Helpers {

		inline void drawRegion(unsigned char *outputGrayArray, Region const * const region, const unsigned char color = 255) {
			for (int i : region->pixels) {
				outputGrayArray[i] = color;
			}

			for (Region * child = region->child; child; child = child->next) {
				drawRegion(outputGrayArray, child, color);
			}
		}

		namespace _internal {
			// internal method, used by regionHierarchyToVector
			inline void regionHierarchyToVector(Region *region, std::vector<Region *> *results) {
				results->push_back(region);

				for (Region * child = region->child; child; child = child->next) {
					_internal::regionHierarchyToVector(child, results);
				}
			}
		}

		/**
		 * returns the number of direct children of the region
		 */
		inline int numberOfChildren(RegionDetector::Region *region) {
			int n = 0;
			for (RegionDetector::Region *child = region->child; child != nullptr; child = child->next) {
				n++;
			}

			return n;
		}

		/**
		 * returns a std::vector containg the region and all of the regions children and children's children
		 */
		inline std::vector<Region*> regionHierarchyToVector(Region * region) {
			std::vector<Region *> results;
			_internal::regionHierarchyToVector(region, &results);
			return results;
		}

		/**
		 * @returns true if the bounding boxes of regionA and regionB overlap
		 */
		inline bool boundingBoxesIntersect(Region const * const regionA, Region const * const regionB) {

			if (regionA->xMin > regionB->xMax) {
				return false;
			}

			if (regionA->yMin > regionB->yMax) {
				return false;
			}

			if (regionB->xMin > regionA->xMax) {
				return false;
			}

			if (regionB->yMin > regionA->yMax) {
				return false;
			}

			return true;
		}

		/**
		 * @ returns true if regionA and regionB, or their children, overlap. Otherwise returns false.
		 */
		inline bool regionsOverlap(Region const * const regionA, Region const * const regionB) {
			if (boundingBoxesIntersect(regionA, regionB)) {
				for (int idxA = 0; idxA < regionA->pixels.size(); idxA++) {
					for (int idxB = 0; idxB < regionB->pixels.size(); idxB++) {
						if (regionA->pixels[idxA] == regionB->pixels[idxB]) {
							return true;
						}
					}
				}

				if (regionA->child) {
					for (Region * childA = regionA->child; childA; childA = childA->next) {
						if (regionsOverlap(childA, regionB)) {
							return true;
						}
					}
				}
				else
				{
					for (Region * childB = regionB->child; childB; childB = childB->next) {
						if (regionsOverlap(childB, regionA)) {
							return true;
						}
					}
				}
			}
			return false;
		}

		/**
		* fills the vector 'pixels' with the indexes of all the pixels of the region and the regions children
		*/
		inline void getAllPixelIdxs(Region const * const region, std::vector<unsigned int> *pixels) {
			assert(region);
			assert(pixels);
			for (std::vector<unsigned int>::const_iterator it = region->pixels.begin(); it != region->pixels.end(); ++it) {
				pixels->push_back(*it);
			}
			for (Region * child = region->child; child; child = child->next) {
				getAllPixelIdxs(child, pixels);
			}
		}

		/**
		 * returns true if (x,y) is contained in the region or the regions children
		 */
		inline bool isXYInRegion(Region *region, int x, int y, int width) {
			int idx = xyToIdx(x, y, width);

			std::vector<unsigned int> idxs;
			getAllPixelIdxs(region, &idxs);

			for (int i = 0; i < idxs.size(); i++) {
				if (idxs[i] == idx) {
					return true;
				}
			}
			return false;
		}

	}
}

#endif
