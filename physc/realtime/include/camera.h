#pragma once
#include <glm.hpp>
#include <ext/matrix_transform.hpp>
#include <shared/defs.hpp>

enum class Direction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera final {
public:

    Camera () {  }

    void move(float factor, const Direction& dir) noexcept;

    void rotate(double x_pos, double y_pos, float dt, bool &initial);

    [[nodiscard]] glm::mat4 view() const noexcept { return glm::lookAt(eye_, eye_ + front_, up_); }

    // vec3 z = front
    // vec3 x = cross(up, z)
    // vec3 y = cross(z, x)

    //

private:
    double last_x_{400.0};
    double last_y_{300.0};
    float camera_sensitivity_{0.001f};
    float yaw_{-89.f};
    float pitch_{0.0f};
    glm::vec3 eye_{0.0f, 0.0f, 2.0f};
    glm::vec3 right_{0.0f};
    glm::vec3 up_{0.0f, 1.0f, 0.0f};
    glm::vec3 front_{0.0f, 0.0f, -1.0f};
};