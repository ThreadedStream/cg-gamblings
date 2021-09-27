#pragma once
#include <glm.hpp>
#include <ext/matrix_transform.hpp>

constexpr auto up = glm::vec3{0.0f, 1.0f, 0.0f};

enum class Direction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera final {
public:

    void move(float factor, const Direction& dir) noexcept;

    void rotate();

    [[nodiscard]] glm::mat4 view() const noexcept { return glm::lookAt(eye_, eye_ + front_, up); }

private:
    glm::vec3 eye_{0.0f, 0.0f, 2.0f};
    glm::vec3 front_{0.0f, 0.0f, -1.0f};
};