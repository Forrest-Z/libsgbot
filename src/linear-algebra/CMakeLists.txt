SET(LA_SRCS
  matrix-std.cpp
  matrix-neon.cpp
)

ADD_LIBRARY(linear-algebra ${LA_SRCS})
