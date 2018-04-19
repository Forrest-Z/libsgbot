cmake_minimum_required(VERSION 2.8.3)
project(libsgbot-drawing)

set(CMAKE_CXX_STANDARD 11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  geometry_msgs
  std_msgs
)

if(NOT DEFINED env{LIBSGBOT_INCLUDE_DIR})
  message(FATAL_ERROR "Not defined environment variable:LIBSGBOT_INCLUDE_DIR")  
endif()

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp geometry_msgs
)

include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
  $env{LIBSGBOT_INCLUDE_DIR}
)
