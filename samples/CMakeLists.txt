PROJECT(libsgbot)

INCLUDE_DIRECTORIES(
  ${PROJECT_SOURCE_DIR}/include
)

LINK_DIRECTORIES(
  ${PROJECT_SOURCE_DIR}/src
)

add_executable(matrix-sample matrix-sample.cpp)
target_link_libraries(matrix-sample sgbot)
