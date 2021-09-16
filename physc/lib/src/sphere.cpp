#include "../include/sphere.h"


bool Sphere::intersects(Ray& r, float& t, const float t_min, const float t_max, HitRecord& hit_record) {
    // Let A be the origin of ray and C be the center of a sphere, then
    // CA = A - C, vector from the center of a sphere to the ray
    // (CA).(CA) - r^2 = 0, where . is a dot(scalar) product between
    // two vectors
    // Given that A = O + t*dir, where O is the origin of the ray, dir - heading direction of a ray,
    // and t is a scaling factor (beware that dir should be normalized beforehand)
    // Simplification of expression above yields:
    // (O + t*dir - C).(O + t*dir - C) - r^2 = 0
    // (CO + t * dir).(CO + t*dir) - r^2 = 0
    // (CO + t*dir).(CO + t*dir) - r^2 = 0
    // |CO|^2 + 2 * CO * t*dir + t^2*|dir|^2 - r^2 = 0 =>
    // t^2*dir^2 + 2 * CO * t*dir + |CO|^2 - r^2 = 0
    // where CO is a vector from center of a sphere to the origin of a ray

    float c_rad_sqr = rad_ * rad_; // r * r = r^2
    glm::vec3 c_r =  r.origin() - center_; // CA = A - C
    const auto direction_ = glm::normalize(r.direction());

    // a
    const float a = glm::dot(direction_, direction_); // (dir).(dir) = |dir|^2
    // b
    const float b = 2 * glm::dot(direction_, c_r); // 2 * dir * CO
    // c
    const float c = glm::dot(c_r, c_r) - static_cast<float>(c_rad_sqr); // |CO|^2 - r^2

    const float discriminant = (b * b - 4 * c);

    if (discriminant < 0) {
        return false;
    }

    const float discriminant_sqrt = sqrt(discriminant);
    const float t1 = (-b + discriminant_sqrt) / 2;
    const float t2 = (-b - discriminant_sqrt) / 2;
    if (t1 < t2 && t1 >= 0.0f){
        hit_record.t = t1;
        hit_record.intersection_point = r.at(t1);
        hit_record.set_face_normal(direction_, (hit_record.intersection_point - center_) / rad_);
    }else if (t2 < t1 && t2 >= 0.0f){
        hit_record.t = t2;
        hit_record.intersection_point = r.at(t2);
        hit_record.set_face_normal(direction_, (hit_record.intersection_point - center_) / rad_);
    }

    return true;
}