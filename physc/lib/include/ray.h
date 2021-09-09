#pragma once

#include "sphere.h"

class Ray {
public:
    explicit Ray(const glm::vec3& origin,const glm::vec3& direction):
        origin_{origin}, direction_{direction} {};

    inline glm::vec3 at(float t) { return origin_ + (direction_ * t); }

    [[nodiscard]] inline glm::vec3 origin() const noexcept { return origin_; }
    [[nodiscard]] inline glm::vec3 direction() const noexcept { return direction_; }

    bool intersectsSphere(const Sphere& sphere, float& t0, float& t1) {

        // c_rad - radius of a sphere
        // c_rad_sqr - squared radius of a sphere
        // c_r - vector from center of a sphere to the origin of a ray
        // dir_mag_sqr - squared magnitude of a ray's direction vector (dot of dir vector with itself)
        // TODO(threadedstream): comment that out properly
        // TODO(threadedstream): try sphere at (0, 0, -1)
        int32_t c_rad = sphere.radius();
        int32_t c_rad_sqr = c_rad * c_rad;
        glm::vec3 c_r = sphere.center() - origin_;
        // a
        const float dir_mag_sqr = glm::dot(direction_, direction_);
        // c
        const float c_r_mag_sqr = glm::dot(c_r, c_r) - static_cast<float>(c_rad_sqr);
        // b
        const float b = 2 * glm::dot(direction_, c_r);

        const float discriminant = (b * b - 4 * dir_mag_sqr * c_r_mag_sqr);

        if (discriminant < 0){
            return false;
        }
        const float discriminant_sqrt = sqrt(discriminant);
        t0 = (-b + discriminant_sqrt) / 2 * dir_mag_sqr;
        t1 = (-b - discriminant_sqrt) / 2 * dir_mag_sqr;

        return true;
    }


private:
    glm::vec3 origin_;
    glm::vec3 direction_;
};