SET(LA_SRCS
  matrixbase-std.cpp
  matrixbase-neon.cpp
)

ADD_LIBRARY(linear-algebra ${LA_SRCS})
