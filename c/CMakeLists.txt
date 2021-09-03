cmake_minimum_required(VERSION 3.19)
project(physc C)

set(CMAKE_CXX_FLAGS "-Wall -S -emit-llvm")

option (USING_LAPTOP "Use laptop configuration" OFF)

option (BUILD_AS_SHARED_LIB "Build physc as a shared lib" OFF)

set(CMAKE_CXX_COMPILER "clang")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")


add_subdirectory(lib)
add_subdirectory(extern/box2d)

