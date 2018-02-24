PROJECT(libsgbot)

INCLUDE_DIRECTORIES(
  ${PROJECT_SOURCE_DIR}/include
)

LINK_DIRECTORIES(
  ${PROJECT_SOURCE_DIR}/src
)

ADD_EXECUTABLE(linear-algebra-base linear-algebra-base.cpp)
TARGET_LINK_LIBRARIES(linear-algebra-base sgbot)
