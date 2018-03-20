SET(HECTOR_SRCS
  map/gridmap/base.cpp
  map/occupancy-gridmap/base.cpp
  map/occupancy-gridmap/optimizer.cpp
)

ADD_LIBRARY(hector ${HECTOR_SRCS})
