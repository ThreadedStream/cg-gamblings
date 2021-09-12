#pragma once

#include "defs.hpp"

class Sphere {
public:
    // for the purpose of demo, we'll limit ourselves to integer values
    explicit Sphere(int32_t x, int32_t y, int32_t z, float rad):
    center_{x, y, z}, rad_{rad}{};

    explicit Sphere(glm::vec3 center, float rad):
    center_{center}, rad_{rad} {};

    [[nodiscard]] inline const glm::vec3& center() const noexcept { return center_; }
    [[nodiscard]] inline const float radius() const noexcept { return rad_; }

private:
    glm::vec3 center_;
    float rad_;
};