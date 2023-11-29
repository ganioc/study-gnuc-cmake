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

add_executable(multargs ./multargs.cpp)

add_executable(excp ./excp.cpp)

add_executable(process ./process.cpp)

add_executable(ipc ./ipc.cpp)

add_executable(ipcpipe ./ipcpipe.cpp)

add_executable(ipcshm ./ipcshm.cpp)

add_executable(ipcexec ./ipcexec.cpp)

add_executable(ipcredir ./ipcredir.cpp)

add_executable(ipcsig ./ipcsig.cpp)

add_executable(ioterm ./ioterm.cpp)
