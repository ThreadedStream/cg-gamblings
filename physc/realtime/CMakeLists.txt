set(GLM_INCLUDE ${CMAKE_SOURCE_DIR}/extern/glm/glm)
set(SPDLOG_INCLUDE ${CMAKE_SOURCE_DIR}/extern/spdlog/include)
set(GLFW_INCLUDE ${CMAKE_SOURCE_DIR}/extern/glfw/include)
set(SDL_INCLUDE /usr/local/include/SDL2)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# i don't like this mess
if (USING_LAPTOP)
    set(SDL_LIB /usr/local/lib/libSDL2.so)
    set(SDL_FONT_LIB /usr/local/lib/libSDL2_ttf.so)
    set(GLU_SHARED_LIB /usr/lib/libGLU.so)
    set(GL_SHARED_LIB /usr/lib/libGL.so)
else()
    set(SDL_LIB /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so)
    set(SDL_FONT_LIB /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so)
    set(GLU_SHARED_LIB /usr/lib/x86_64-linux-gnu/libGLU.so)
    set(GL_SHARED_LIB /usr/lib/x86_64-linux-gnu/libGL.so)
endif()

set(GLM_SHARED_LIB ${CMAKE_SOURCE_DIR}/extern/glm/build/glm/libglm_shared.so)
set(SPDLOG_SHARED_LIB ${CMAKE_SOURCE_DIR}/extern/spdlog/build/libspdlog.so)
set(GLFW_SHARED_LIB ${CMAKE_SOURCE_DIR}/extern/glfw/build/src/libglfw.so)

set(REALTIME_SRC_FILES
        src/main.cpp)

set(REALTIME_HEADER_FILES
        )

add_executable(realtime ${REALTIME_SRC_FILES} ${REALTIME_HEADER_FILES})
target_include_directories(realtime
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        ${GLM_INCLUDE}
        ${SDL_INCLUDE}
        ${GLFW_INCLUDE}
        PRIVATE
        ${SPDLOG_INCLUDE}
        ${CMAKE_SOURCE_DIR}
        "/usr/include/c++"
        "/usr/include/"
        )

set(CMAKE_CXX_STANDARD 17)

target_link_libraries(realtime ${SDL_LIBRARIES} ${SDL_LIB}
                                ${SDL_FONT_LIB} ${SDL2_IMAGE_LIBRARIES}
                                ${GLM_SHARED_LIB} ${GLFW_SHARED_LIB}
                                ${GLU_SHARED_LIB} ${GL_SHARED_LIB})

set_target_properties(realtime PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED yes
        )
