#pragma once

#include "defs.hpp"
#include "hittable.h"

class Plane : public Hittable {
public:
    explicit Plane(const glm::vec3 &normal, const glm::vec3& point) :
            normal_{normal}, point_{point} {};

    explicit Plane(const float x, const float y, const float z, const glm::vec3& point) :
            normal_{x, y, z}, point_{point} {};

    bool intersects(Ray& r, float& t, float t_min, float t_max, HitRecord& hit_record);

    bool intersectsOther(const Plane &plane) {
        const glm::vec3 normalized_normal = glm::normalize(normal_);
        return glm::dot(normalized_normal, glm::normalize(plane.normal_)) == 0.0;
    }

    glm::vec3 chooseRandomPointOnPlane() {
        glm::vec3 b1, b2;
        buildOrthonormalBasis(b1, b2);
        return b1;
    }

    // http://jcgt.org/published/0006/01/01/
    inline void buildOrthonormalBasis(glm::vec3 &b1, glm::vec3 &b2) {
        const glm::vec3 normal = glm::normalize(normal_);
        const float sign = copysignf(1.0f, normal.z);
        const float a = -1.0f / (sign + normal.z);
        const float b = normal.x * normal.y * a;
        b1 = glm::vec3(1.0f + sign * normal.x * normal.x * a,
                       sign * b, -sign * normal.x);
        b2 = glm::vec3(b, sign + normal.y * normal.y * a, -normal.y);
    }

    [[maybe_unused]] [[nodiscard]] inline glm::vec3 &normal() noexcept { return normal_; }

    [[maybe_unused]] [[nodiscard]] inline glm::vec3& point() noexcept { return point_; }

private:
    glm::vec3 normal_;
    glm::vec3 point_;
};