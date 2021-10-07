#pragma once

#include "scene.h"
#include <glm.hpp>
#include "camera.h"
#include "filesystem.h"

struct GLFWwindow;

class LightingScene : public Scene {
public:
    LightingScene();

    void draw();

    void setup() override;

    inline void handleInput(GLFWwindow *window, float dt) {
        handleKeyboardInput(window, dt);
    }

    void destroy() override;

private:
    void prepareBufferObjects() override;

    void prepareTextureData() override;

    void handleKeyboardInput(GLFWwindow *window, float dt);

private:
    uint32_t vao_;
    uint32_t vbo_;
    uint32_t shader_program_id_;
    glm::mat4 projection_;
    glm::mat4 model_;
    glm::vec4 ambient_color_{0.4f, 0.2f, 0.4f, 1.0f};
    glm::vec4 diffuse_color_{0.2f, 0.3f, 0.5f, 1.0f};
    glm::vec4 specular_color_{0.0f, 0.5f, 0.2f, 1.0f};
    Camera camera_;
    bool dirty_;
};