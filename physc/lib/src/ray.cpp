#include "../include/ray.h"
#include "../include/ppm.h"
#include "../include/camera.h"

#include <iostream>
#include <include/plane.h>

// (p - p0).n = 0
// let (p - p0) be P0P
// P0P.n = 0 => (P0P.x * n.x) + (P0P.y * n.y) + (P0P.z * n.z) = 0
//

glm::vec3 Ray::determineColor(const bool has_intersection, float& t) {
    if (has_intersection){
        return glm::vec3{1.0f, 1.0f, 0.0f};
    }else{
        // TODO(threadedstream): the name "defaultColor" would be better
        return defaultColor();
    }
}

