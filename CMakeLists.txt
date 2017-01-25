CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(RegionDetector)
SET(CMAKE_CXX_FLAGS "-std=c++0x")

INCLUDE_DIRECTORIES(RegionDetector)

INCLUDE(tests/CMakeLists.txt)

ADD_EXECUTABLE(RegionDetectorExample 
	example.cpp
)
