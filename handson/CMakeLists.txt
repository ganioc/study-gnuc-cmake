cmake_minimum_required(VERSION 3.6)
project(handson)

find_package(Git REQUIRED)

set(CMAKE_CXX_STANDARD 17)

# Guideline Support ARGS 
list(APPEND GSL_CMAKE_ARGS
    -DGSL_TEST=ON
    -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}
)

include(ExternalProject)

ExternalProject_Add(
    gsl 
    GIT_REPOSITORY https://github.com/Microsoft/GSL.git 
    GIT_SHALLOW 1
    GIT_TAG  main
    CMAKE_ARGS ${GSL_CMAKE_ARGS} 
    PREFIX ${CMAKE_BINARY_DIR}/external/gsl/prefix 
    TMP_DIR ${CMAKE_BINARY_DIR}/external/gsl/tmp 
    STAMP_DIR ${CMAKE_BINARY_DIR}/external/gsl/stamp 
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/external/gsl/download 
    SOURCE_DIR ${CMAKE_BINARY_DIR}/external/gsl/src 
    BINARY_DIR ${CMAKE_BINARY_DIR}/external/gsl/build
)

# Executable
include_directories(${CMAKE_BINARY_DIR}/include)

add_executable(example1 example1.cpp)
add_dependencies(example1 gsl)
