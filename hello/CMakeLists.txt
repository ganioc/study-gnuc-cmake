project(helloworld CXX)

set(CMAKE_CXX_STANDARD 14)

set(SRCS ./hello.cpp)

add_executable(hello ${SRCS})

