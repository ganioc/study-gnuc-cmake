project(helloworld CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS_DEBUG "-g")

set(SRCS ./hello.cpp)


include_directories(include)
include_directories(../libs/GSL/include)

# find_package(GSL REQUIRED)
# link_libraries(GSL::gsl)
# include_directories(${GSL_INCLUDE_DIRS})
# link_directories(${GSL_LIBRARY_DIRS})


add_executable(hello ${SRCS})

