#include "../include/ray.h"
#include "../include/ppm.h"
#include "../include/camera.h"

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
            const glm::vec3 ray_color = defaultColor();
            manipulator.writeSingle(ray_color);
        }
    }
}

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

glm::vec3 Ray::determineColor(Ray& r, const Sphere& sphere, float& t) {
    if (r.intersectsSphere(sphere, t)){
        // return yellow-ish color upon a successful intersection
        return glm::vec3{0.0f, 1.0f, 0.0f};
    }else{
        // TODO(threadedstream): the name "defaultColor" would be better
        return defaultColor();
    }
}

void Ray::castNumerousRaysIntoScene(const int32_t width,const int32_t height) {
    Camera camera(width, height);

    PPManipulator manipulator{"/home/threadedstream/sample.ppm", width, height, 255};
    // TODO(threadedstream): provide better error diagnostic?
    if (!manipulator.handle()) { return; }

    float t{0.0f}, u{0.0f}, v{0.0f};
    Sphere sphere(0, 0, -20, 10);

    // TODO(threadedstream): Benchmark it
    for (int32_t j = height - 1; j >= 0; j--){
        for (int32_t i = 0; i < width - 1; i++) {
            u = static_cast<float>(i) / static_cast<float>(width - 1);
            v = static_cast<float>(j) / static_cast<float>(height - 1);
            Ray r = camera.castRay(u, v);
            const glm::vec3 color = r.determineColor(r, sphere, t);
            manipulator.writeSingle(color);
        }
    }
}

