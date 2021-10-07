# replace set's with find_path's
set(GLM_INCLUDE ${CMAKE_SOURCE_DIR}/extern/glm/glm)
set(SPDLOG_INCLUDE ${CMAKE_SOURCE_DIR}/extern/spdlog/include)
set(GLFW_INCLUDE ${CMAKE_SOURCE_DIR}/extern/glfw/include)
set(STB_INCLUDE ${CMAKE_SOURCE_DIR}/extern/stb/)
set(GLAD_INCLUDE ${CMAKE_SOURCE_DIR}/extern/glad)

if (UNIX)
    find_package(SDL2 REQUIRED)
    find_package(SDL2_mixer REQUIRED)
elseif(WIN32)
    set(SDL2_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/extern/SDL2/include)
    set(SDL2_LIB ${CMAKE_SOURCE_DIR}/extern/SDL2/lib/x64/SDL2.lib )
    set(SDL2_MIXER_LIB ${CMAKE_SOURCE_DIR}/extern/SDL2/lib/x64/SDL2_mixer.lib )
   # set(SDL2_MIXER_SHARED_LIB ${CMAKE_SOURCE_DIR}/extern/SDL2/lib/x64/SDL2_mixer.dll)
endif()

find_library(GLFW_LIB NAMES glfw3dll.lib libglfw.so HINTS ${CMAKE_SOURCE_DIR}/extern/glfw/build/src
                                                              ${CMAKE_SOURCE_DIR}/extern/glfw/build/src/Debug)

find_library(FREETYPE_SHARED_LIB NAMES libfreetype.so.6 HINTS ${USR_LIB_GNU})

if (UNIX)
    set(TARGET_LINK_LIBRARIES ${GLFW_SHARED_LIB} SDL2::Core SDL2::Mixer X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread ${FREETYPE_SHARED_LIB})
elseif(WIN32)
    set(TARGET_LINK_LIBRARIES ${GLFW_LIB} ${SDL2_LIB} ${SDL2_MIXER_LIB})
endif()

add_library(STB_IMAGE_LIB ${CMAKE_SOURCE_DIR}/extern/stb/stb_image.cpp)
add_library(GLAD_LIB ${CMAKE_SOURCE_DIR}/extern/glad/glad.c)

set(TARGET_LINK_LIBRARIES  GLAD_LIB ${TARGET_LINK_LIBRARIES} STB_IMAGE_LIB)


set(REALTIME_SRC_FILES
        src/renderer.cpp
        src/shader.cpp
        src/sample_scene.cpp
        src/camera.cpp
        src/lighting_scene.cpp
        src/audio.cpp
        src/main.cpp
        )

set(REALTIME_HEADER_FILES
        include/shader.h
        include/vertices.h
        include/shader_sources.h
        include/renderer.h
        include/sample_scene.h
        include/scene.h
        include/camera.h
        include/lighting_scene.h
        include/audio.h
        include/scene_manager.h include/filesystem.h)

add_executable(realtime ${REALTIME_SRC_FILES} ${REALTIME_HEADER_FILES})
target_include_directories(realtime
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        ${GLM_INCLUDE}
        ${SDL2_INCLUDE_DIRS}
        ${STB_INCLUDE}
        ${GLFW_INCLUDE}
        ${GLAD_INCLUDE}
        PRIVATE
        ${SPDLOG_INCLUDE}
        ${CMAKE_SOURCE_DIR}
        "/usr/include/c++"
        "/usr/include/"
        )

set(CMAKE_CXX_STANDARD 17)

target_link_libraries(realtime ${TARGET_LINK_LIBRARIES})

set_target_properties(realtime PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED yes
        )
