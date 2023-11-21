project(helloc C)

set(CMAKE_C_STANDARD 99)

# debug flag
#set(CMAKE_C_FLAGS_DEBUG "-g")

set(SRCS ./hello.c)

add_executable(helloc ${SRCS})

add_executable(prolog ./prolog.c)

add_executable(args ./args.c)

# add_executable(multargs ./multargs.c)

