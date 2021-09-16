#include "../include/ray.h"
#include "../include/ppm.h"
#include "../include/camera.h"

#include <iostream>
#include <include/plane.h>

// (p - p0).n = 0
// let (p - p0) be P0P
// P0P.n = 0 => (P0P.x * n.x) + (P0P.y * n.y) + (P0P.z * n.z) = 0
//

glm::vec3 Ray::determineColor(Ray& r, Scene& scene, const int32_t depth) {
    HitRecord hit_record{};
    if (depth <= 0) {
        return Color{0.0f, 0.0f, 0.0f};
    }
    if (scene.getClosestT(r, hit_record)){
        Point3 target = hit_record.intersection_point + hit_record.normal + random_point_in_unit_sphere(20);
        auto new_ray = Ray(hit_record.intersection_point, target - hit_record.intersection_point);
        return determineColor(new_ray, scene, depth - 1);
    }else{
        return defaultColor();
    }
}

