#include "../include/ray.h"
#include "../include/ppm.h"
#include "../include/camera.h"

#include <iostream>
#include <include/plane.h>

// (p - p0).n = 0
// let (p - p0) be P0P
// P0P.n = 0 => (P0P.x * n.x) + (P0P.y * n.y) + (P0P.z * n.z) = 0
//

glm::vec3 Ray::determineColor(const bool has_intersection, const glm::vec3& normal, float& t) {
    if (has_intersection){
        return glm::vec3{normal.x + 1.0f, normal.y + 1.0f, normal.z + 1.0f} * 2.0f;
    }else{
        return defaultColor();
    }
}

