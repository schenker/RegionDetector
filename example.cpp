#include "RegionDetector/RegionDetector.hpp"
#include "RegionDetector/RegionAllocator.hpp"
#include "RegionDetector/RegionDetectorHelpers.hpp"

#include <iostream>

int main() {

	const unsigned int width = 10;
	const unsigned int height = 10;

	uint8_t * pixels = new uint8_t[width*height];

	std::fill_n(pixels, width*height, 255); // fill our test image with white pixels

	// create 2 darker regions within the white background region
	pixels[14] = 20;
	pixels[15] = 20;

	pixels[44] = 10;
	pixels[45] = 10;
	pixels[46] = 10;

	RegionDetector::RegionAllocator<RegionDetector::Region> allocator;
	RegionDetector::RegionDetectorDetector<RegionDetector::Region, RegionDetector::RegionAllocator<RegionDetector::Region>> detector;

	RegionDetector::Region *rootRegion = detector.detect(pixels, width, height, &allocator);

	std::vector<RegionDetector::Region*> regions = RegionDetector::Helpers::regionHierarchyToVector(rootRegion);

	// we found three regions, the top level region of size 100 and the two small regions of size 2 and 3
	std::cout << "found " << regions.size() << " regions" << std::endl;

	// print region information
	for (int i = 0; i < regions.size(); i++) {
		RegionDetector::Region *region = regions[i];
		std::cout << "region " << i << " size: " << region->size
			<< ", number of direct child regions: " << RegionDetector::Helpers::numberOfChildren(region)
			<< ", average intensity: " << region->getMeanIntensity() << std::endl;
	}

	delete[] pixels;

	return EXIT_SUCCESS;
}
