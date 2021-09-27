#pragma once

#include "scene.h"
#include <functional>
#include <glm.hpp>
#include <include/camera.h>

struct GLFWwindow;

class SampleScene : public Scene {
public:
    SampleScene();

    void draw();

    void setup() override;

    void destroy() override;

    void handleInput(GLFWwindow* window, float dt);

private:
    void prepareBufferObjects() override;

    void prepareTextureData() override;

    void mouseCallback(GLFWwindow* window, double x_pos, double y_pos);

private:
    uint32_t shader_program_id_{0};
    uint32_t wall_texture_{0};
    uint32_t face_texture_{0};
    // TODO(threadedstream): should be in camera class
    float camera_speed_{10.f};
    glm::mat4 projection_{1.0f};
    glm::mat4 model_{1.0f};
    Camera camera;
    bool first_mouse_{true};
    bool dirty_{false};
};
