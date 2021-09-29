# replace set's with find_path's
set(GLM_INCLUDE ${CMAKE_SOURCE_DIR}/extern/glm/glm)
set(SPDLOG_INCLUDE ${CMAKE_SOURCE_DIR}/extern/spdlog/include)
set(GLFW_INCLUDE ${CMAKE_SOURCE_DIR}/extern/glfw/include)
set(SDL_INCLUDE /usr/local/include/SDL2)
set(STB_INCLUDE ${CMAKE_SOURCE_DIR}/extern/stb/)
set(GLAD_INCLUDE ${CMAKE_SOURCE_DIR}/extern/glad)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

set(USR_LOCAL_LIB /usr/local/lib/)
set(USR_LIB /usr/lib/)
set(USR_LIB_GNU /usr/lib/x86_64-linux-gnu/)

find_library(GLFW_SHARED_LIB NAMES libglfw.so HINTS ${CMAKE_SOURCE_DIR}/extern/glfw/build/src)
find_library(FREETYPE_SHARED_LIB NAMES libfreetype.so.6 HINTS ${USR_LIB_GNU})

set(TARGET_LINK_LIBRARIES ${GLFW_SHARED_LIB} X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread ${FREETYPE_SHARED_LIB})

#find_library(SDL_LIB NAMES libSDL2.so HINTS ${USR_LOCAL_LIB} ${USR_LIB_GNU})
#find_library(GLU_SHARED_LIB NAMES libGLU.so HINTS ${USR_LIB} ${USR_LIB_GNU})
#find_library(GL_SHARED_LIB NAMES libGL.so HINTS ${USR_LIB} ${USR_LIB_GNU})
#find_library(GLM_SHARED_LIB NAMES libglm_shared.so HINTS ${CMAKE_SOURCE_DIR}/extern/glm/build/glm)
#find_library(SPDLOG_SHARED_LIB NAMES libspdlog.so HINTS ${CMAKE_SOURCE_DIR}/extern/spdlog/build)

add_library(STB_IMAGE_LIB ${CMAKE_SOURCE_DIR}/extern/stb/stb_image.cpp)
add_library(GLAD_LIB ${CMAKE_SOURCE_DIR}/extern/glad/glad.c)

set(TARGET_LINK_LIBRARIES  GLAD_LIB ${TARGET_LINK_LIBRARIES} STB_IMAGE_LIB)


set(REALTIME_SRC_FILES
        src/main.cpp
        src/renderer.cpp
        src/shader.cpp
        src/sample_scene.cpp
        src/camera.cpp
        src/lighting_scene.cpp
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
        )

add_executable(realtime ${REALTIME_SRC_FILES} ${REALTIME_HEADER_FILES})
target_include_directories(realtime
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        ${GLM_INCLUDE}
        ${SDL_INCLUDE}
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

set(LIB)

target_link_libraries(realtime ${TARGET_LINK_LIBRARIES})

set_target_properties(realtime PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED yes
        )
