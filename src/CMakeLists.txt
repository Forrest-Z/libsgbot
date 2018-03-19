PROJECT(libsgbot)

option(USE_ARM_NEON		"Set to support ARM NEON instructions"	OFF)

IF(${USE_ARM_NEON} STREQUAL "ON")
  ADD_DEFINITIONS(-D_USE_ARM_NEON_)
  MESSAGE("Compile linear algebra with ARM NEON")
ELSE()
  ADD_DEFINITIONS(-D_USE_STD_ARITHMETIC_)
  MESSAGE("Compile linear algebra with STD arithmetic")
ENDIF()

SET(STANDALONE_SRCS
)

#Add sub source directories
ADD_SUBDIRECTORY(linear-algebra)
ADD_SUBDIRECTORY(std-math)
ADD_SUBDIRECTORY(transform)
ADD_SUBDIRECTORY(distribution)
ADD_SUBDIRECTORY(slam)

ADD_LIBRARY(sgbot SHARED ${STANDALONE_SRCS})

TARGET_LINK_LIBRARIES(sgbot
  linear-algebra
  std-math
  transform
  distribution
  slam
)
