# A fast 2D Region Detector
Based on the MSER Algorithm from "Linear Time Maximally Stable Extremal Regions" by David Nistér and Henrik Stewénius.

## Usage

```
uint8_t * pixels = ...
unsigned int width = ...
unsigned int height = ...	

typedef RegionDetector::RegionAllocator<RegionDetector::Region> AllocatorType;
typedef RegionDetector::RegionDetectorDetector<RegionDetector::Region, AllocatorType> DetectorType;

DetectorType detector;
AllocatorType allocator;

RegionDetector::Region *rootRegion = detector.detect(pixels, width, height, &allocator);
	
std::vector<RegionDetector::Region*> regions = RegionDetector::Helpers::regionHierarchyToVector(rootRegion);
```

## License
This software is licensed under the [MIT](LICENSE) license.
