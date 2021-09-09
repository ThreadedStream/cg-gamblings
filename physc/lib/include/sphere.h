#pragma once

#include "defs.hpp"

class Sphere {
public:
    // for the purpose of demo, we'll limit ourselves to integer values
    explicit Sphere(int32_t x, int32_t y, int32_t z, int32_t rad):
    center_{x, y, z}, rad_{rad}{};

    explicit Sphere(glm::vec3 center, int32_t rad):
    center_{center}, rad_{rad} {};

    [[nodiscard]] inline const glm::vec3& center() const noexcept { return center_; }
    [[nodiscard]] inline const int32_t radius() const noexcept { return rad_; }

private:
    glm::vec3 center_;
    int32_t rad_;
};