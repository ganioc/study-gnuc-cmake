project(helloc C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS_DEBUG "-g")

set(SRCS ./hello.c)

add_executable(helloc ${SRCS})