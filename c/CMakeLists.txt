cmake_minimum_required(VERSION 3.19)
project(physc C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

if (DEFINED ENV{"laptop"})
    set(SDL_LIB /usr/local/lib/libSDL2.so)
else()
    set(SDL_LIB /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so)
endif()

set(SDL_FONT_LIB /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so)

set(SDL_INCLUDE /usr/local/include/SDL2)

add_executable(physc render.c utils.c draw.c main.c entity.h animation.h animation.c asset_loader.h)
target_include_directories(physc PUBLIC ${SDL_INCLUDE})
target_link_libraries(physc ${SDL_LIBRARIES} ${SDL_LIB} ${SDL_FONT_LIB} ${SDL2_IMAGE_LIBRARIES} )
