#include "../include/plane.h"
#include "../include/ray.h"

bool Plane::intersects(Ray &r, float &t, const float t_min, const float t_max) {
    //TODO(threadedstream): avoid normalizing normal each time during computations --
    // normalize it in ctor instead
    const glm::vec3 normalized_normal = glm::normalize(normal_);

    const auto numerator = glm::dot(glm::normalize(point_ - r.origin()), normalized_normal);
    const auto denominator = glm::dot(glm::normalize(r.direction()), normalized_normal);

    // WARNING(threadedstream): this code looks very subtle and does not
    // seem to be correct approach to tackle this sort of problems.
    // I would rather use approximate equality in this case
    t = numerator / denominator;

    return t >= t_min && t <= t_max;
}