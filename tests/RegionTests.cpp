#include "catch.hpp"
#include "RegionDetector/Region.hpp"

using namespace RegionDetector;

TEST_CASE("region constructor test 1") {
	Region region(7);
	REQUIRE(region.level == 7);

	REQUIRE(region.child == nullptr);
	REQUIRE(region.next == nullptr);
	REQUIRE(region.parent == nullptr);

	REQUIRE(region.size == 0);

	REQUIRE(region.xMin == -1);
	REQUIRE(region.yMin == -1);
	REQUIRE(region.xMax == -1);
	REQUIRE(region.yMax == -1);

	REQUIRE(region.intensitySum == 0);
}

TEST_CASE("region constructor test 2") {
	Region region;

	REQUIRE(region.child == nullptr);
	REQUIRE(region.next == nullptr);
	REQUIRE(region.parent == nullptr);

	REQUIRE(region.size == 0);

	REQUIRE(region.xMin == -1);
	REQUIRE(region.yMin == -1);
	REQUIRE(region.xMax == -1);
	REQUIRE(region.yMax == -1);

	REQUIRE(region.intensitySum == 0);
}

TEST_CASE("region accumulate test 1") {
	Region region(0);

	region.accumulate(0, 1, 5);
	REQUIRE(region.size == 1);
	REQUIRE(region.getMeanIntensity() == 1);

	REQUIRE(region.xMin == 0);
	REQUIRE(region.xMax == 0);
	REQUIRE(region.yMin == 0);
	REQUIRE(region.yMax == 0);
}

TEST_CASE("region accumulate test 2") {
	Region region(0);

	region.accumulate(0, 0, 5);
	region.accumulate(5, 0, 5);

	REQUIRE(region.xMin == 0);
	REQUIRE(region.xMax == 0);
	REQUIRE(region.yMin == 0);
	REQUIRE(region.yMax == 1);
}

TEST_CASE("region accumulate test 3") {
	Region region(0);

	region.accumulate(0, 0, 5);
	region.accumulate(6, 0, 5);

	REQUIRE(region.xMin == 0);
	REQUIRE(region.xMax == 1);
	REQUIRE(region.yMin == 0);
	REQUIRE(region.yMax == 1);
}

TEST_CASE("region accumulate test 4") {
	Region region;
	region.accumulate(2, 0, 5);

	REQUIRE(region.xMin == 2);
	REQUIRE(region.xMax == 2);
	REQUIRE(region.yMin == 0);
	REQUIRE(region.yMax == 0);
}

TEST_CASE("region accumulate test 5") {
	Region region;
	region.accumulate(2, 0, 5);
	region.accumulate(0, 0, 5);

	REQUIRE(region.xMin == 0);
	REQUIRE(region.xMax == 2);
	REQUIRE(region.yMin == 0);
	REQUIRE(region.yMax == 0);
}

TEST_CASE("merge 1") {

	Region regionA(0);
	regionA.accumulate(0, 0, 5);

	Region regionB(1);
	regionB.accumulate(1, 0, 5);
	regionB.accumulate(2, 0, 5);

	Region regionC(0);
	regionC.accumulate(3, 0, 5);

	regionA.merge(&regionB);
	regionC.merge(&regionA);

	REQUIRE(regionA.size == 3);
	REQUIRE(regionB.size == 2);
	REQUIRE(regionC.size == 4);


	REQUIRE(regionC.child == &regionA);
	REQUIRE(regionA.child == &regionB);


	REQUIRE(regionA.parent == &regionC);
	REQUIRE(regionB.parent == &regionA);
	REQUIRE(regionC.parent == nullptr);

	REQUIRE(regionA.next == nullptr);
	REQUIRE(regionA.next == nullptr);
	REQUIRE(regionA.next == nullptr);
}

TEST_CASE("merge 2") {

	Region regionA(0);
	regionA.accumulate(0, 0, 5);

	Region regionB(1);
	regionB.accumulate(1, 0, 5);

	Region regionC(0);
	regionC.accumulate(2, 0, 5);

	regionA.merge(&regionB);
	regionA.merge(&regionC);

	REQUIRE(regionA.child == &regionC);
	REQUIRE(regionC.next == &regionB);
}

TEST_CASE("merge 3") {
	Region region1;
	region1.accumulate(0, 0, 5);
	Region region2;
	region2.accumulate(1, 0, 5);

	REQUIRE(region1.xMin == 0);
	REQUIRE(region1.xMax == 0);
	REQUIRE(region1.yMin == 0);
	REQUIRE(region1.yMax == 0);

	region1.merge(&region2);

	REQUIRE(region1.xMin == 0);
	REQUIRE(region1.xMax == 1);
	REQUIRE(region1.yMin == 0);
	REQUIRE(region1.yMax == 0);
}

TEST_CASE("merge 4") {
	Region region1;
	region1.accumulate(0, 0, 5);
	Region region2;
	region2.accumulate(1, 0, 5);

	region1.merge(&region2);

	REQUIRE(region1.xMin == 0);
	REQUIRE(region1.xMax == 1);
	REQUIRE(region1.yMin == 0);
	REQUIRE(region1.yMax == 0);
}

TEST_CASE("merge 5") {
	Region region1;
	region1.accumulate(0, 0, 5);
	Region region2;
	region2.accumulate(2, 0, 5);

	region1.merge(&region2);

	REQUIRE(region1.xMin == 0);
	REQUIRE(region1.xMax == 2);
	REQUIRE(region1.yMin == 0);
	REQUIRE(region1.yMax == 0);
}
