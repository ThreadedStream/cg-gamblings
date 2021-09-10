cmake_minimum_required(VERSION 3.19)
project(physc)

set(CMAKE_CXX_STANDARD 17)

set(CLANG_FLAGS "-fdiagnostics-format=msvc -pedantic -fsave-optimization-record=yaml -foptimization-record-file=opt.log -fsanitize=address")

set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_FLAGS ${CLANG_FLAGS})


option (USING_LAPTOP "Use laptop configuration" OFF)

option (BUILD_AS_SHARED_LIB "Build physc as a shared lib" OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_subdirectory(lib)

