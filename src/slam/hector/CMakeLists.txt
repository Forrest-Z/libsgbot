SET(HECTOR_SRCS
  map/gridmap/base.cpp
  map/occupancy-gridmap/base.cpp
  map/occupancy-gridmap/optimizer.cpp
  slam/processor.cpp
  slam/scanmatcher.cpp
  mapping.cpp
)

ADD_LIBRARY(hector ${HECTOR_SRCS})
