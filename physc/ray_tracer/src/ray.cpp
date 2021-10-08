#include "../include/ray.h"
#include "../include/ppm.h"
#include "../include/camera.h"

#include <iostream>
#include <include/plane.h>

#include <include/material.h>

// (p - p0).n = 0
// let (p - p0) be P0P
// P0P.n = 0 => (P0P.x * n.x) + (P0P.y * n.y) + (P0P.z * n.z) = 0
//

class Material;

Color Ray::determineColor(Ray &r, Scene &scene, const int32_t depth) {
    HitRecord hit_record{};
    if (depth <= 0) {
        return colors[BLACK];
    }

    if (scene.getClosestT(r, hit_record)) {
        Ray scattered;
        Color attenuation;
        if (hit_record.material->scatter(r, hit_record, attenuation, scattered))
            return attenuation * determineColor(scattered, scene, depth - 1) ;

        return colors[BLACK];
    }

    return defaultColor();
}

