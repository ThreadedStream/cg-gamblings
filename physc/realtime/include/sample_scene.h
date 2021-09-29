#pragma once

#include "scene.h"
#include <functional>
#include <include/camera.h>
#include <shared/defs.hpp>

struct GLFWwindow;

class SampleScene : public Scene {
public:
    SampleScene();

    void draw();

    void setup() override;

    void destroy() override;

    inline void handleInput(GLFWwindow* window, float dt) {
        handleKeyboardInput(window, dt);
        handleMouseInput(window, dt);
    }

private:
    void prepareBufferObjects() override;

    void prepareTextureData() override;

    void handleKeyboardInput(GLFWwindow* window, float dt);

    void handleMouseInput(GLFWwindow* window, float dt);

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
    double last_mouse_pos_x_{HALF_WIDTH};
    double last_mouse_pos_y_{HALF_HEIGHT};
};
