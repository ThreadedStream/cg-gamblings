set(PHYSC_SRC_FILES
        src/animation.c
        src/draw.c
        src/main.c
        src/map.c
        src/memory.c
        src/render.c
        src/utils.c)

set(PHYSC_HEADER_FILES
        include/animation.h
        include/asset_loader.h
        include/defs.h
        include/draw.h
        include/entity.h
        include/map.h
        include/memory.h
        include/render.h
        include/utils.h)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

if (USING_LAPTOP)
    set(SDL_LIB /usr/local/lib/libSDL2.so)
else()
    set(SDL_LIB /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so)
endif()

set(SDL_FONT_LIB /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so)

set(SDL_INCLUDE /usr/local/include/SDL2)

set(BOX2D_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/extern/box2d/include)

add_library(physc ${PHYSC_SRC_FILES} ${PHYSC_HEADER_FILES})
target_include_directories(physc
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        ${SDL_INCLUDE}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(physc ${SDL_LIBRARIES} ${SDL_LIB} ${SDL_FONT_LIB} ${SDL2_IMAGE_LIBRARIES})

set_target_properties(physc PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED yes
        )

