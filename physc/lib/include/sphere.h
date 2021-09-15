#pragma once

#include "defs.hpp"
#include "hittable.h"
#include "ray.h"

class Sphere : public Hittable {
public:
    explicit Sphere(int32_t x, int32_t y, int32_t z, float rad):
    center_{x, y, z}, rad_{rad}{};

    explicit Sphere(const glm::vec3& center, float rad):
    center_{center}, rad_{rad} {};

    bool intersects(Ray& r, float& t, float t_min, float t_max, HitRecord& hit_record);

    [[maybe_unused]] [[nodiscard]] inline const glm::vec3& center() const noexcept { return center_; }
    [[maybe_unused]] [[nodiscard]] inline float radius() const noexcept { return rad_; }

private:
    glm::vec3 center_;
    float rad_;
};