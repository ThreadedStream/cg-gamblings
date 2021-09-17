#pragma once

#include "defs.hpp"
#include "hittable.h"
#include "ray.h"


class Sphere : public Hittable {
public:
    explicit Sphere(int32_t x, int32_t y, int32_t z, float rad,const  std::shared_ptr<Material>& mat) :
            center_{x, y, z}, material_{mat}, rad_{rad} {};

    explicit Sphere(const glm::vec3 &center, float rad, const std::shared_ptr<Material> &mat) :
            center_{center}, material_{mat}, rad_{rad} {};

    bool intersects(Ray &r, float &t, float t_min, float t_max, HitRecord &hit_record);

    [[maybe_unused]] [[nodiscard]] inline const glm::vec3 &center() const noexcept { return center_; }

    [[maybe_unused]] [[nodiscard]] inline float radius() const noexcept { return rad_; }

    [[maybe_unused]] [[nodiscard]] inline Material *material() noexcept { return material_.get(); }


private:
    glm::vec3 center_;
    // can pointer be omitted?
    std::shared_ptr<Material> material_;
    float rad_;
};