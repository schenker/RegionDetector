#ifndef _REGIONDETECTOR_REGIONALLOCATOR_HPP_
#define _REGIONDETECTOR_REGIONALLOCATOR_HPP_

#include "Region.hpp"

#include <vector>
#include <cassert>

namespace RegionDetector {

	template <class REGION_TYPE> class RegionAllocator {
	private:
		std::vector<std::vector<REGION_TYPE>> pool;
		size_t chunkPos;
		size_t regionPos;
		const size_t chunkSize;

		void addChunk() {
			pool.push_back(std::vector<REGION_TYPE>(chunkSize));
			chunkPos++;
			regionPos = 0;
		}

	public:
		RegionAllocator(const int chunkSize = 20 * 1024) : chunkPos(0), regionPos(0), chunkSize(chunkSize) {
			assert(chunkSize > 0);
			pool.push_back(std::vector<REGION_TYPE>(chunkSize));
		}

		~RegionAllocator() {
			pool.clear();
		}

		REGION_TYPE* new_(const unsigned int level) {
			REGION_TYPE *region = new(&pool[chunkPos][regionPos++]) REGION_TYPE(level);
			assert(region);
			if (regionPos == chunkSize) {
				addChunk();
			}
			return region;
		}
	};

}
#endif
