#include "catch.hpp"
#include "RegionDetector/IdxHelpers.hpp"

using namespace RegionDetector::Helpers;

TEST_CASE("idxToX test 1") {
	REQUIRE(idxToX(0, 10) == 0);
}

TEST_CASE("idxToX test 2") {
	REQUIRE(idxToX(10, 10) == 0);
}

TEST_CASE("idxToX test 3") {
	REQUIRE(idxToX(11, 10) == 1);
}

TEST_CASE("idxToY test 1") {
	REQUIRE(idxToY(0, 10) == 0);
}

TEST_CASE("idxToY test 2") {
	REQUIRE(idxToY(10, 10) == 1);
}

TEST_CASE("idxToY test 3") {
	REQUIRE(idxToY(11, 10) == 1);
}

TEST_CASE("xyToIdx test 1") {
	REQUIRE(xyToIdx(0, 0, 10) == 0);
}

TEST_CASE("xyToIdx test 2") {
	REQUIRE(xyToIdx(1, 0, 10) == 1);
}

TEST_CASE("xyToIdx test 3") {
	REQUIRE(xyToIdx(0, 1, 10) == 10);
}

TEST_CASE("xyToIdx test 4") {
	REQUIRE(xyToIdx(4, 5, 10) == 54);
}

TEST_CASE("xyToIdx test 5") {
	REQUIRE(xyToIdx(5, 4, 10) == 45);
}
