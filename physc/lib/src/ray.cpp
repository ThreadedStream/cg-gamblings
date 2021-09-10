#include "../include/ray.h"
#include "../include/ppm.h"


void Ray::sampleRayCasting(const int32_t width, const int32_t height) {

    const float aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
    // setup a camera
    const float viewport_height = 2.0;
    const float viewport_width = aspect_ratio * viewport_height;
    const float focal_length = 1.0;

    PPManipulator manipulator{"/home/glasser/sample.ppm", width, height, 260};
    // TODO(threadedstream): provide better error diagnostic?
    if (!manipulator.handle()) { return; }

    const auto origin = glm::vec3{0, 0, 0};
    const auto horizontal = glm::vec3{viewport_width, 0, 0};
    const auto vertical = glm::vec3{0, viewport_height, 0};
    const glm::vec3 lower_left_corner =
            origin - (horizontal / 2.0f) - (vertical / 2.0f) - glm::vec3(0, 0, focal_length);

    float u{0.0f}, v{0.0f};
    // TODO(threadedstream): consider enable parallelism by means of OMP extension
    for (int32_t j = height - 1; j >= 0; j--) {
        for (int32_t i = 0; i < width; i++) {
            u = static_cast<float>(i) / static_cast<float>(width - 1);
            v = static_cast<float>(j) / static_cast<float>(height - 1);
            origin_ = origin;
            direction_ = lower_left_corner + u * horizontal + v * vertical - origin_;
            const glm::vec3 ray_color = rayColor();
            manipulator.writeSingle(ray_color);
        }
    }
}

bool Ray::intersectsSphere(const Sphere& sphere, float& t){
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

    if (discriminant < 0) {
        return false;
    }
    const float discriminant_sqrt = sqrt(discriminant);
    // TODO(threadedstream): add a second root as well
    t = (-b + discriminant_sqrt) / 2 * dir_mag_sqr;

    return true;

}

glm::vec3 Ray::determineColor(const Sphere& sphere, float& t) {
    if (intersectsSphere(sphere, t)){
        // return yellow-ish color upon a successful intersection
        return glm::vec3{0.0f, 1.0f, 0.0f};
    }else{
        // TODO(threadedstream): the name "defaultColor" would be better
        return glm::vec3{1.0f, 1.0f, 1.0f};
    }
}

void Ray::castNumerousRaysIntoScene(const int32_t width,const int32_t height) {
    const float aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
    // setup a camera
    const float viewport_height = 2.0;
    const float viewport_width = aspect_ratio * viewport_height;
    const float focal_length = 1.0;

    PPManipulator manipulator{"/home/glasser/sample.ppm", width, height, 255};
    // TODO(threadedstream): provide better error diagnostic?
    if (!manipulator.handle()) { return; }

    const auto origin = glm::vec3{0, 0, 0};
    const auto horizontal = glm::vec3{viewport_width, 0, 0};
    const auto vertical = glm::vec3{0, viewport_height, 0};
    const glm::vec3 lower_left_corner =
            origin - (horizontal / 2.0f) - (vertical / 2.0f) - glm::vec3(0, 0, focal_length);

    float t{0.0f}, u{0.0f}, v{0.0f};
    Sphere sphere(0, 0, -20, 10);

    // TODO(threadedstream): Benchmark it
    for (int32_t j = height - 1; j >= 0; j--){
        for (int32_t i = 0; i < width - 1; i++) {
            u = static_cast<float>(i) / static_cast<float>(width - 1);
            v = static_cast<float>(j) / static_cast<float>(height - 1);
            Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            const glm::vec3 color = r.determineColor(sphere, t);
            manipulator.writeSingle(color);
        }
    }
}

