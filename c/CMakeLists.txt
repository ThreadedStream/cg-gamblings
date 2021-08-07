cmake_minimum_required(VERSION 3.19)
project(physc C)

set(CMAKE_C_STANDARD 11)
set(SDL2_INCLUDE_DIR .SDL2/source/include)
set(SDL2_LIB /home/threadedstream/toys/godot-math-physics/c/SDL2/lib/libSDL2-2.0.so.0.4.1)
set(SDL2_GFX_LIB /usr/local/lib/libSDL2_gfx.so)

add_executable(physc main.c)

target_include_directories(physc PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(physc ${SDL2_LIB} ${SDL2_GFX_LIB})
