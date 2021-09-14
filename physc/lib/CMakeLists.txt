set(BOX2D_INCLUDE ../extern/box2d/include)

set(GLM_INCLUDE ${CMAKE_SOURCE_DIR}/extern/glm/glm)

set(BOX2D_SRC ${CMAKE_SOURCE_DIR}/extern/box2d/src)

set(SPDLOG_INCLUDE ${CMAKE_SOURCE_DIR}/extern/spdlog/include)

set(PHYSC_SRC_FILES
        src/animation.cpp
        src/draw.cpp
        src/main.cpp
        src/map.cpp
        src/memory.cpp
        src/render.cpp
        src/ray.cpp
        src/camera.cpp
        src/sphere.cpp
        src/plane.cpp
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
        include/broker.h
        include/ray.h
        include/ppm.h
        include/camera.h
        include/plane.h
        include/scene.h
        include/hittable.h
        )


find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

if (USING_LAPTOP)
    set(SDL_LIB /usr/local/lib/libSDL2.so)
    set(SDL_FONT_LIB /usr/local/lib/libSDL2_ttf.so)
else()
    set(SDL_LIB /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so)
    set(SDL_FONT_LIB /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so)
endif()

set(GLM_SHARED_LIB ${CMAKE_SOURCE_DIR}/extern/glm/build/glm/libglm_shared.so)
set(BOX2D_SHARED_LIB ${CMAKE_SOURCE_DIR}/extern/box2d/build/bin/libbox2d.so)

set(SPDLOG_SHARED_LIB ${CMAKE_SOURCE_DIR}/extern/spdlog/build/libspdlog.so)

set(SDL_INCLUDE /usr/local/include/SDL2)

add_executable(physc ${PHYSC_SRC_FILES} ${PHYSC_HEADER_FILES})
target_include_directories(physc
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        ${SDL_INCLUDE}
        ${GLM_INCLUDE}
        ${BOX2D_INCLUDE}
        ${BOX2D_SRC}
        PRIVATE
        ${SPDLOG_INCLUDE}
        ${CMAKE_CURRENT_SOURCE_DIR}
        "/usr/include/c++"
        "/usr/include/"
        )

target_link_libraries(physc ${SDL_LIBRARIES} ${SDL_LIB} ${SDL_FONT_LIB} ${BOX2D_SHARED_LIB} ${SDL2_IMAGE_LIBRARIES} ${GLM_SHARED_LIB})

set_target_properties(physc PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED yes
        )

