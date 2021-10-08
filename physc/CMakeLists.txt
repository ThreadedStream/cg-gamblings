cmake_minimum_required(VERSION 3.19)
project(physc)

set(CMAKE_CXX_STANDARD 17)

# dump syntax tree for clang
set(CLANG_FLAGS "-Weverything -pedantic ")
set(GCC_FLAGS "-Wall")

option(USING_LAPTOP "Use laptop configuration" OFF)

option(BUILD_AS_SHARED_LIB "Build physc as a shared lib" OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

if (CMAKE_BUILD_TYPE=Release)
    if (CMAKE_CXX_COMPILER STREQUAL "MSVC")
        set(OPTIMIZATION_FLAG "/O2")
    else()
        set(OPTIMIZATION_FLAG "-O2")
    endif()
endif()

if (CMAKE_CXX_COMPILER STREQUAL "Clang")

endif()


add_compile_options(-gdwarf-4)


add_subdirectory(realtime)
add_subdirectory(ray_tracer)

