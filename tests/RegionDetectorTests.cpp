#include "catch.hpp"

#include "RegionDetector/Region.hpp"
#include "RegionDetector/RegionAllocator.hpp"
#include "RegionDetector/RegionDetector.hpp"
#include "RegionDetector/RegionDetectorHelpers.hpp"

using namespace RegionDetector;

TEST_CASE("RegionDetectorDetector 1") {

	class CustomRegion : public Region {
	public:
		CustomRegion(int i) : Region(i) {}
		CustomRegion() {}
		int CustomMember = 0;
	};

	RegionAllocator<CustomRegion> allocator;
	RegionDetectorDetector<CustomRegion, RegionAllocator<CustomRegion>> RegionDetectorDetector;

	unsigned char pixels[1];

	CustomRegion *rootRegion = RegionDetectorDetector.detect(pixels, 1, 1, &allocator);

	REQUIRE(rootRegion->parent == nullptr);
	REQUIRE(rootRegion->child == nullptr);
	REQUIRE(rootRegion->next == nullptr);
	REQUIRE(rootRegion->size == 1);
}

TEST_CASE("RegionDetectorDetector 2") {
	RegionAllocator<Region> allocator;
	RegionDetectorDetector<Region, RegionAllocator<Region>> RegionDetectorDetector;

	const unsigned int width = 98;
	const unsigned int height = 101;

	unsigned char pixels[width*height];

	for (int i = 0; i < width*height; i++) {
		pixels[i] = 100;
	}

	pixels[100] = 3;
	pixels[101] = 4;
	pixels[102] = 5;
	pixels[103] = 4;

	Region *rootRegion = RegionDetectorDetector.detect(pixels, width, height, &allocator);

	REQUIRE(rootRegion->parent == nullptr);
	REQUIRE(rootRegion->child != nullptr);
	REQUIRE(rootRegion->next == nullptr);
	REQUIRE(rootRegion->size == width*height);

	REQUIRE(Helpers::regionHierarchyToVector(rootRegion).size() == 5);
}

TEST_CASE("RegionDetectorDetector 3") {
	RegionAllocator<Region> allocator;
	RegionDetectorDetector<Region, RegionAllocator<Region>> RegionDetectorDetector;

	Region *rootRegion = RegionDetectorDetector.detect(nullptr, 1, 0, &allocator);
	REQUIRE(rootRegion == nullptr);
}

TEST_CASE("RegionDetectorDetector 4") {
	RegionAllocator<Region> allocator;
	RegionDetectorDetector<Region, RegionAllocator<Region>> RegionDetectorDetector;

	Region *rootRegion = RegionDetectorDetector.detect(nullptr, 0, 1, &allocator);
	REQUIRE(rootRegion == nullptr);
}
