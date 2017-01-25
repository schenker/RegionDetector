#include "catch.hpp"
#include "RegionDetector/RegionDetectorHelpers.hpp"

using namespace RegionDetector;

TEST_CASE("boundingBoxesIntersect test 1") {
	Region regionA;
	Region regionB;

	regionA.xMin = 0;
	regionA.xMax = 0;
	regionA.yMin = 0;
	regionA.yMax = 0;

	regionB.xMin = 1;
	regionB.xMax = 1;
	regionB.yMin = 1;
	regionB.yMax = 1;

	REQUIRE_FALSE(Helpers::boundingBoxesIntersect(&regionA, &regionB));
}

TEST_CASE("boundingBoxesIntersect test 2") {
	Region regionA;
	Region regionB;

	regionA.xMin = 0;
	regionA.xMax = 1;
	regionA.yMin = 0;
	regionA.yMax = 1;

	regionB.xMin = 0;
	regionB.xMax = 1;
	regionB.yMin = 0;
	regionB.yMax = 1;

	REQUIRE(Helpers::boundingBoxesIntersect(&regionA, &regionB));
}

TEST_CASE("boundingBoxesIntersect test 3") {
	Region regionA;
	Region regionB;

	regionA.xMin = 0;
	regionA.xMax = 10;
	regionA.yMin = 0;
	regionA.yMax = 10;

	regionB.xMin = 8;
	regionB.xMax = 18;
	regionB.yMin = 8;
	regionB.yMax = 18;

	REQUIRE(Helpers::boundingBoxesIntersect(&regionA, &regionB));
}

TEST_CASE("boundingBoxesIntersect test 4") {
	Region regionA;
	Region regionB;

	regionA.xMin = 0;
	regionA.xMax = 0;
	regionA.yMin = 0;
	regionA.yMax = 0;

	regionB.xMin = 0;
	regionB.xMax = 0;
	regionB.yMin = 0;
	regionB.yMax = 0;

	REQUIRE(Helpers::boundingBoxesIntersect(&regionA, &regionB));
}

TEST_CASE("boundingBoxesIntersect test 5") {
	Region region1;
	region1.accumulate(0, 0, 5);
	Region region2;
	region2.accumulate(1, 0, 5);

	region1.merge(&region2);

	REQUIRE(Helpers::boundingBoxesIntersect(&region1, &region2));
}

TEST_CASE("boundingBoxesIntersect test 6") {
	Region region1;
	region1.accumulate(0, 0, 5);
	Region region2;
	region2.accumulate(1, 0, 5);

	region1.merge(&region2);

	Region region3;
	region3.accumulate(1, 0, 5);

	REQUIRE(Helpers::boundingBoxesIntersect(&region1, &region3));
	REQUIRE(Helpers::boundingBoxesIntersect(&region3, &region1));
}

TEST_CASE("boundingBoxesIntersect test 7") {
	Region region1;
	region1.accumulate(0, 0, 5);
	Region region2;
	region2.accumulate(1, 0, 5);

	region1.merge(&region2);

	Region region3;
	region3.accumulate(1, 0, 5);

	REQUIRE(Helpers::boundingBoxesIntersect(&region3, &region1));
	REQUIRE(Helpers::boundingBoxesIntersect(&region1, &region3));
}

TEST_CASE("boundingBoxesIntersect test 8") {
	Region region1;
	region1.accumulate(1, 0, 5);
	Region region2;
	region2.accumulate(0, 0, 5);

	region1.merge(&region2);

	Region region3;
	region3.accumulate(1, 0, 5);

	REQUIRE(Helpers::boundingBoxesIntersect(&region3, &region1));
	REQUIRE(Helpers::boundingBoxesIntersect(&region1, &region3));
}

TEST_CASE("boundingBoxesIntersect test 9") {
	Region region;
	region.accumulate(0, 0, 5);

	REQUIRE(Helpers::boundingBoxesIntersect(&region, &region));
}

TEST_CASE("boundingBoxesIntersect test 10") {
	Region region1;
	region1.accumulate(0, 0, 5);
	Region region2;
	region2.accumulate(1, 0, 5);

	region1.merge(&region2);

	Region region3;
	region3.accumulate(3, 0, 5);

	REQUIRE_FALSE(Helpers::boundingBoxesIntersect(&region3, &region1));
	REQUIRE_FALSE(Helpers::boundingBoxesIntersect(&region1, &region3));
}

TEST_CASE("boundingBoxesIntersect test 11") {
	Region region1;
	region1.accumulate(0, 0, 5);
	Region region2;
	region2.accumulate(2, 0, 5);

	region1.merge(&region2);

	Region region3;
	region3.accumulate(0, 0, 5);
	region3.accumulate(2, 0, 5);

	REQUIRE(Helpers::boundingBoxesIntersect(&region1, &region3));
	REQUIRE(Helpers::boundingBoxesIntersect(&region3, &region1));
}

TEST_CASE("boundingBoxesIntersect test 12") {
	Region region1;
	region1.accumulate(0, 0, 5);
	Region region2;
	region2.accumulate(2, 0, 5);

	region1.merge(&region2);

	Region region3;
	region3.accumulate(0, 0, 5);

	REQUIRE(Helpers::boundingBoxesIntersect(&region1, &region3));
	REQUIRE(Helpers::boundingBoxesIntersect(&region3, &region1));
}

TEST_CASE("boundingBoxesIntersect test 13") {
	Region region1;
	region1.accumulate(0, 0, 5);
	Region region2;
	region2.accumulate(2, 0, 5);

	region1.merge(&region2);

	Region region3;
	region3.accumulate(1, 0, 5);

	REQUIRE(Helpers::boundingBoxesIntersect(&region1, &region3));
	REQUIRE(Helpers::boundingBoxesIntersect(&region3, &region1));
}

TEST_CASE("boundingBoxesIntersect test 14") {
	Region region1;
	region1.accumulate(0, 0, 5);
	Region region2;
	region2.accumulate(1, 0, 5);
	region2.accumulate(2, 0, 5);

	region2.merge(&region1);

	Region region3;
	region3.accumulate(2, 0, 5);

	REQUIRE(Helpers::boundingBoxesIntersect(&region2, &region3));
	REQUIRE(Helpers::boundingBoxesIntersect(&region3, &region2));
}

TEST_CASE("boundingBoxesIntersect test 15") {
	Region region1;
	region1.accumulate(0, 0, 15);
	Region region2;
	region2.accumulate(5, 0, 15);

	region1.merge(&region2);

	Region region3;
	region3.accumulate(5, 0, 15);

	REQUIRE(Helpers::boundingBoxesIntersect(&region1, &region3));
	REQUIRE(Helpers::boundingBoxesIntersect(&region3, &region1));
}

TEST_CASE("boundingBoxesIntersect test 16") {
	Region region1;
	region1.accumulate(0, 0, 5);
	Region region2;
	region2.accumulate(2, 0, 5);

	region2.merge(&region1);

	Region region3;
	region3.accumulate(2, 0, 5);
	region3.accumulate(3, 0, 5);

	REQUIRE(Helpers::boundingBoxesIntersect(&region2, &region3));
	REQUIRE(Helpers::boundingBoxesIntersect(&region3, &region2));
}

TEST_CASE("regionsOverlap test 1") {
	Region regionA;
	Region regionB;

	regionA.xMin = 0;
	regionA.xMax = 0;
	regionA.yMin = 0;
	regionA.yMax = 0;

	regionB.xMin = 1;
	regionB.xMax = 1;
	regionB.yMin = 1;
	regionB.yMax = 1;

	// bounding boxes do not overlap
	REQUIRE_FALSE(Helpers::regionsOverlap(&regionA, &regionB));
}

TEST_CASE("regionsOverlap test 2") {
	Region regionA;
	Region regionB;

	regionA.xMin = 0;
	regionA.xMax = 1;
	regionA.yMin = 0;
	regionA.yMax = 1;

	regionB.xMin = 0;
	regionB.xMax = 1;
	regionB.yMin = 0;
	regionB.yMax = 1;

	// bounding boxes overlap, but pixels do not overlap
	REQUIRE_FALSE(Helpers::regionsOverlap(&regionA, &regionB));

	regionA.pixels.push_back(0);
	regionB.pixels.push_back(0);

	// pixel 0 belongs to both regions now
	REQUIRE(Helpers::regionsOverlap(&regionA, &regionB));
}

TEST_CASE("regionsOverlap test 3") {
	Region region;

	region.xMin = 0;
	region.xMax = 1;
	region.yMin = 0;
	region.yMax = 1;

	// bounding boxes overlap, but pixels do not overlap
	REQUIRE_FALSE(Helpers::regionsOverlap(&region, &region));

	region.pixels.push_back(0);

	// pixel 0 belongs to both regions now
	REQUIRE(Helpers::regionsOverlap(&region, &region));
}

TEST_CASE("regionsOverlap test 4") {
	Region region;

	region.xMin = 0;
	region.xMax = 0;
	region.yMin = 0;
	region.yMax = 0;

	// bounding boxes overlap, but pixels do not overlap
	REQUIRE_FALSE(Helpers::regionsOverlap(&region, &region));

	region.pixels.push_back(0);

	// pixel 0 belongs to both regions
	REQUIRE(Helpers::regionsOverlap(&region, &region));
}

TEST_CASE("regionsOverlap test 5") {
	Region region1;
	region1.accumulate(0, 0, 5);
	Region region2;
	region2.accumulate(1, 0, 5);

	region1.merge(&region2);

	REQUIRE(Helpers::regionsOverlap(&region1, &region2));
	REQUIRE(Helpers::regionsOverlap(&region2, &region1));
}

TEST_CASE("regionsOverlap test 6") {
	Region region1;
	region1.accumulate(0, 0, 5);
	Region region2;
	region2.accumulate(1, 0, 5);

	region1.merge(&region2);

	Region region3;
	region3.accumulate(1, 0, 5);

	REQUIRE(Helpers::regionsOverlap(&region1, &region3));
}

TEST_CASE("regionsOverlap test 7") {
	Region region1;
	region1.accumulate(0, 0, 5);
	Region region2;
	region2.accumulate(1, 0, 5);

	region1.merge(&region2);

	Region region3;
	region3.accumulate(1, 0, 5);

	REQUIRE(Helpers::regionsOverlap(&region3, &region1));
}

TEST_CASE("regionsOverlap test 8") {
	Region region1;
	region1.accumulate(0, 0, 5);
	Region region2;
	region2.accumulate(3, 0, 5);

	region1.merge(&region2);

	Region region3;
	region3.accumulate(2, 0, 5);

	REQUIRE_FALSE(Helpers::regionsOverlap(&region3, &region1));
	REQUIRE_FALSE(Helpers::regionsOverlap(&region1, &region3));
}

TEST_CASE("regionsOverlap test 9") {
	Region region1;
	region1.accumulate(0, 0, 5);
	Region region2;
	region2.accumulate(2, 0, 5);

	region1.merge(&region2);

	Region region3;
	region3.accumulate(2, 0, 5);

	REQUIRE(Helpers::regionsOverlap(&region3, &region1));
}

TEST_CASE("regionsOverlap test 10") {
	Region region1;
	region1.xMin = 0;
	region1.yMin = 1;
	region1.xMax = 0;
	region1.yMax = 1;

	Region region2;
	region2.xMin = 0;
	region2.yMin = 0;
	region2.xMax = 0;
	region2.yMax = 0;

	REQUIRE_FALSE(Helpers::regionsOverlap(&region1, &region2));
	REQUIRE_FALSE(Helpers::regionsOverlap(&region2, &region1));
}

TEST_CASE("regionsOverlap test 11") {
	Region region1;
	region1.accumulate(0, 0, 5);
	Region region2;
	region2.accumulate(2, 0, 5);

	region1.merge(&region2);

	Region region3;
	region3.accumulate(7, 0, 5);

	Region region4;
	region4.accumulate(2, 0, 5);

	region3.merge(&region4);

	REQUIRE(Helpers::regionsOverlap(&region1, &region3));
	REQUIRE(Helpers::regionsOverlap(&region3, &region1));
}

TEST_CASE("drawRegion test 1") {
	Region r;
	r.accumulate(0, 0, 100);
	r.accumulate(10, 0, 100);

	Region r2;
	r2.accumulate(11, 0, 100);

	r.merge(&r2);

	unsigned char pixels[100];
	for (int i = 0; i < 100; i++) {
		pixels[i] = 0;
	}

	Helpers::drawRegion(&pixels[0], &r, 1);
	REQUIRE(pixels[0] == 1);
	REQUIRE(pixels[10] == 1);
	REQUIRE(pixels[11] == 1);
	REQUIRE(pixels[12] == 0);

	Helpers::drawRegion(&pixels[0], &r, 2);
	REQUIRE(pixels[0] == 2);
	REQUIRE(pixels[10] == 2);
	REQUIRE(pixels[11] == 2);
	REQUIRE(pixels[12] == 0);

	Helpers::drawRegion(&pixels[0], &r, 0);

	for (int i = 0; i < 100; i++) {
		REQUIRE(pixels[i] == 0);
	}
}

TEST_CASE("regionHierarchyToVector test 1") {
	Region r(1);
	REQUIRE(Helpers::regionHierarchyToVector(&r).size() == 1);
}

TEST_CASE("regionHierarchyToVector test 2") {
	Region r1(1);
	Region r2(2);
	Region r3(3);
	Region r4(3);

	r1.child = &r2;
	r2.child = &r3;
	r2.next = &r4;

	REQUIRE(Helpers::regionHierarchyToVector(&r1).size() == 4);
}

TEST_CASE("getAllPixelIdxs test 1") {
	Region r;
	std::vector<unsigned int> pixels;
	Helpers::getAllPixelIdxs(&r, &pixels);
	REQUIRE(pixels.empty());
}

TEST_CASE("getAllPixelIdxs test 2") {
	Region r;
	r.accumulate(0, 0, 5);
	std::vector<unsigned int> pixels;
	Helpers::getAllPixelIdxs(&r, &pixels);
	REQUIRE(pixels.size() == 1);
}

TEST_CASE("getAllPixelIdxs test 3") {
	Region r1;
	r1.accumulate(0, 0, 5);
	Region r2;
	r2.accumulate(1, 0, 5);
	r1.merge(&r2);
	std::vector<unsigned int> pixels;
	Helpers::getAllPixelIdxs(&r1, &pixels);
	REQUIRE(pixels.size() == 2);
}

TEST_CASE("isXYInRegion test 1") {
	Region r;
	REQUIRE(!Helpers::isXYInRegion(&r, 0, 0, 5));
}

TEST_CASE("isXYInRegion test 2") {
	Region r;
	r.accumulate(0, 0, 5);
	REQUIRE(Helpers::isXYInRegion(&r, 0, 0, 5));
}

TEST_CASE("isXYInRegion test 3") {
	Region r;
	r.accumulate(0, 0, 5);
	REQUIRE(!Helpers::isXYInRegion(&r, 1, 0, 5));
	REQUIRE(!Helpers::isXYInRegion(&r, 0, 1, 5));
}

TEST_CASE("isXYInRegion test 4") {
	Region r;
	r.accumulate(10, 0, 5);
	REQUIRE(!Helpers::isXYInRegion(&r, 0, 0, 5));
	REQUIRE(!Helpers::isXYInRegion(&r, 0, 1, 5));
	REQUIRE(Helpers::isXYInRegion(&r, 0, 2, 5));
	REQUIRE(!Helpers::isXYInRegion(&r, 0, 3, 5));
}

TEST_CASE("numberOfChildren test 1") {
	Region r;
	REQUIRE(Helpers::numberOfChildren(&r) == 0);
}

TEST_CASE("numberOfChildren test 2") {
	Region r1;
	Region r2;

	r1.merge(&r2);

	REQUIRE(Helpers::numberOfChildren(&r1) == 1);
}

TEST_CASE("numberOfChildren test 3") {
	Region r1;
	Region r2;
	Region r3;

	r1.merge(&r2);
	r2.merge(&r3);

	REQUIRE(Helpers::numberOfChildren(&r1) == 1);
}

TEST_CASE("numberOfChildren test 4") {
	Region r1;
	Region r2;
	Region r3;

	r1.merge(&r2);
	r1.merge(&r3);

	REQUIRE(Helpers::numberOfChildren(&r1) == 2);
}
