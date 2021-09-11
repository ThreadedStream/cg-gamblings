#include "../include/ray.h"
#include "../include/ppm.h"
#include "../include/camera.h"


bool Ray::intersectsSphere(const Sphere& sphere, float& t){
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
    int32_t c_rad = sphere.radius(); // r
    int32_t c_rad_sqr = c_rad * c_rad; // r * r = r^2
    glm::vec3 c_r =  origin_ - sphere.center(); // CA = A - C

    // a
    const float a = glm::dot(direction_, direction_); // (dir).(dir) = |dir|^2
    // b
    const float b = 2 * glm::dot(direction_, c_r); // 2 * dir * CO
    // c
    const float c = glm::dot(c_r, c_r) - static_cast<float>(c_rad_sqr); // |CO|^2 - r^2

    const float discriminant = (b * b - 4 * a * c); //

    if (discriminant < 0) {
        return false;
    }

    const float discriminant_sqrt = sqrt(discriminant);
    // TODO(threadedstream): add a second root as well
    t = (-b + discriminant_sqrt) / 2 * a;

    return true;

}

glm::vec3 Ray::determineColor(const Sphere& sphere, float& t) {
    if (intersectsSphere(sphere, t)){
        return glm::vec3{1.0f, 1.0f, 0.0f};
    }else{
        // TODO(threadedstream): the name "defaultColor" would be better
        return defaultColor();
    }
}

