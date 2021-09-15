#include "../include/plane.h"
#include "../include/ray.h"

bool Plane::intersects(Ray &r, float &t, const float t_min, const float t_max, HitRecord& hit_record) {
    //TODO(threadedstream): avoid normalizing normal each time during computations --
    // normalize it in ctor instead
    const glm::vec3 normalized_normal = glm::normalize(normal_);

    const auto numerator = glm::dot(glm::normalize(point_ - r.origin()), normalized_normal);
    const auto denominator = glm::dot(glm::normalize(r.direction()), normalized_normal);

    // WARNING(threadedstream): this code looks very subtle and does not
    // seem to be correct approach to tackle this sort of problems.
    // I would rather use approximate equality in this case
    hit_record.t = numerator / denominator;
    hit_record.intersection_point = r.at(t);
    // Not really sure if it's a correct way to compute normal of an intersection
    hit_record.normal = (hit_record.intersection_point - point_);

    return hit_record.t >= t_min && hit_record.t <= t_max;
}