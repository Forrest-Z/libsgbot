SET(DISTR_SRCS
  gaussian-std.cpp
  functions-std.cpp
  gaussian-neon.cpp
  functions-neon.cpp
)

ADD_LIBRARY(distribution ${DISTR_SRCS})
