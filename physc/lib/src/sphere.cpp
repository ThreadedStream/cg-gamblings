#include "../include/sphere.h"


bool Sphere::intersects(Ray& r, float& t, const float t_min, const float t_max) {
    // Let A be the origin of ray and C be the center of a sphere, then
    // CA = A - C, vector from the center of a sphere to the ray
    // (CA).(CA) - r^2 = 0, where . is a dot(scalar) product between
    // two vectors
    // Given that A = O + t*dir, where O is the origin of the ray, dir - heading direction of a ray,
    // and t is a scaling factor (beware that dir should be normalized beforehand)
    // Simplification of expression above yields:
    // (O + t*dir - C).(O + t*dir - C) - r^2 = 0 =>
    // (CO + t*dir).(CO + t*dir) - r^2 = 0
    // |CO|^2 + 2 * CO * t*dir + t^2*|dir|^2 - r^2 = 0 =>
    // t^2*dir^2 + 2 * CO * t*dir + |CO|^2 - r^2 = 0
    // where CO is a vector from center of a sphere to the origin of a ray
    float c_rad_sqr = rad_ * rad_; // r * r = r^2
    glm::vec3 c_r =  r.origin() - center_; // CA = A - C
    const auto direction_ = r.direction();

    // a
    const float a = glm::dot(direction_, direction_); // (dir).(dir) = |dir|^2
    // b
    const float b = 2 * glm::dot(direction_, c_r); // 2 * dir * CO
    // c
    const float c = glm::dot(c_r, c_r) - static_cast<float>(c_rad_sqr); // |CO|^2 - r^2

    const float discriminant = (b * b - 4 * a * c);

    if (discriminant < 0) {
        return false;
    }

    const float discriminant_sqrt = sqrt(discriminant);
    t = (-b + discriminant_sqrt) / 2 * a;
    // TODO(threadedstream): is there a way to avoid branches
    if (t < t_min || t > t_max) {
        t = (-b - discriminant_sqrt) / 2 * a;
        if (t < t_min || t > t_max) {
            return false;
        }
    }

    return true;

}