cmake_minimum_required(VERSION 2.8.3)
project(libsgbot-hector)

set(CMAKE_CXX_STANDARD 11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  nav_msgs
  visualization_msgs
  tf
  message_filters
  laser_geometry
  geometry_msgs
  std_msgs
)

if(NOT DEFINED env{LIBSGBOT_INCLUDE_DIR})
  message(FATAL_ERROR "Not defined environment variable:LIBSGBOT_INCLUDE_DIR")  
endif()

if(NOT DEFINED env{LIBSGBOT_LIB_DIR})
  message(FATAL_ERROR "Not defined environment variable:LIBSGBOT_LIB_DIR")  
endif()

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp geometry_msgs nav_msgs visualization_msgs tf message_filters laser_geometry std_msgs
)

include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
  $env{LIBSGBOT_INCLUDE_DIR}
)

add_executable(libsgbot-hector src/main.cpp)

add_dependencies(libsgbot-hector libsgbot-drawing)

target_link_libraries(libsgbot-hector
  ${catkin_LIBRARIES}
  sgbot
)
