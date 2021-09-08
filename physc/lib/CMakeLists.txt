set(BOX2D_INCLUDE ../extern/box2d/include)

set(BOX2D_SRC ${CMAKE_CURRENT_SOURCE_DIR}/extern/box2d/src)

set(PHYSC_SRC_FILES
        src/animation.cpp
        src/draw.cpp
        src/main.cpp
        src/map.cpp
        src/memory.cpp
        src/render.cpp
        )

set(PHYSC_HEADER_FILES
        include/animation.h
        include/asset_loader.h
        include/defs.hpp
        include/draw.h
        include/entity.h
        include/map.h
        include/memory.h
        include/render.h
        )

set(CMAKE_CXX_FLAGS "-Wno-unused-label -Wall")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

if (USING_LAPTOP)
    set(SDL_LIB /usr/local/lib/libSDL2.so)
    set(SDL_FONT_LIB /usr/local/lib/libSDL2_ttf.so)
    set(BOX2D_SHARED_LIB /home/threadedstream/toys/physc/physc/extern/box2d/build/bin/libbox2d.so)
else()
    set(SDL_LIB /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so)
    set(SDL_FONT_LIB /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so)
    set(BOX2D_SHARED_LIB ../extern/box2d/build/bin/libbox2d.so)
endif()


set(SDL_INCLUDE /usr/local/include/SDL2)

add_executable(physc ${PHYSC_SRC_FILES} ${PHYSC_HEADER_FILES})
target_include_directories(physc
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        ${SDL_INCLUDE}
        ${BOX2D_INCLUDE}
        ${BOX2D_SRC}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        "/usr/include/c++"
        "/usr/include/"
        )

target_link_libraries(physc ${SDL_LIBRARIES} ${SDL_LIB} ${SDL_FONT_LIB} ${BOX2D_SHARED_LIB} ${SDL2_IMAGE_LIBRARIES})

set_target_properties(physc PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED yes
        )

