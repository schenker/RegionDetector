#ifndef __REGIONDETECTOR_IDXHELPERS_HPP__
#define __REGIONDETECTOR_IDXHELPERS_HPP__

#include <cassert>
#include <cmath>

namespace RegionDetector {
	namespace Helpers {

		/**
		 * @returns the x coordinate of the pixel at index idx in an image with the given width
		 */
		inline int idxToX(const int idx, const int stride) {
			assert(stride > 0);
			return idx % stride;
		}

		/**
		 * @returns the y coordinate of the pixel at index idx in an image with the given width
		 */
		inline int idxToY(const int idx, const int stride) {
			assert(stride > 0);
			return idx / stride;
		}

		/**
		 * calculates the index of the pixel at position (x, y) in an image with the given width
		 */
		inline int xyToIdx(const int x, const int y, const int width) {
			return y*width + x;
		}

	}
}

#endif
