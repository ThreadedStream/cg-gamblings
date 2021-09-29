#pragma once

#include "scene.h"
#include <glm.hpp>
#include "camera.h"

class GLFWwindow;

class LightingScene : Scene {
public:
    LightingScene();

    void draw();

    void setup();

    inline void handleInput(GLFWwindow* window, const float dt) {
        handleKeyboardInput(window, dt);
    }

private:
    void prepareBufferObjects() override;

    void prepareTextureData() override;

    void handleKeyboardInput(GLFWwindow* window, float dt);

private:
    uint32_t vao_;
    uint32_t vbo_;
    uint32_t shader_program_id_;
    glm::mat4 projection_;
    glm::mat4 model_;
    Camera camera_;
    bool dirty_;
};