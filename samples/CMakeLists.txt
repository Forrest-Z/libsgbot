SET(Boost_USE_STATIC_LIBS  ON)
SET(Boost_USE_MULTITHREADED  ON)
SET(Boost_USE_STATIC_RUNTIME  OFF)
FIND_PACKAGE(Boost 1.36.0 COMPONENTS date_time filesystem system thread)
if(NOT Boost_FOUND)
  MESSAGE(FATAL_ERROR "Can't find boost library!")
endif()

INCLUDE_DIRECTORIES(
  ${PROJECT_SOURCE_DIR}/include
  ${Boost_INCLUDE_DIRS}
)

LINK_DIRECTORIES(
  ${PROJECT_SOURCE_DIR}/src
  ${Boost_LIBRARIES}
)

ADD_EXECUTABLE(matrix-sample matrix-sample.cpp)
TARGET_LINK_LIBRARIES(matrix-sample sgbot boost_system boost_thread)

ADD_EXECUTABLE(tf-sample tf-sample.cpp)
TARGET_LINK_LIBRARIES(tf-sample sgbot boost_system boost_thread)

ADD_EXECUTABLE(vector-sample vector-sample.cpp)
TARGET_LINK_LIBRARIES(vector-sample sgbot boost_system boost_thread)

ADD_EXECUTABLE(logit-sample logit-sample.cpp)
TARGET_LINK_LIBRARIES(logit-sample sgbot boost_system boost_thread)
