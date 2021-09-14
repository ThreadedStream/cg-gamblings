#include "../include/camera.h"
#include <include/ppm.h>

void Camera::castNumerousRaysIntoScene(const int32_t width,const int32_t height){
    //TODO(threadedstream): adapt the path
    PPManipulator manipulator{"/home/threadedstream/sample.ppm", width, height, 255};
    // TODO(threadedstream): provide an error diagnostic?
    if (!manipulator.handle()) { return; }

    Plane plane(glm::vec3{0.0f, 0.0f, -50.0f}, glm::vec3{10.0f, 20.0f, -20.0f});
    float t{0.0f}, u{0.0f}, v{0.0f};
    Sphere sphere{0, 0, -10, 2.5f};
    glm::vec3 color;

    // TODO(threadedstream): Benchmark it
    for (int32_t j = height - 1; j >= 0; j--){
        for (int32_t i = 0; i < width - 1; i++) {
            u = static_cast<float>(i) / static_cast<float>(width - 1);
            v = static_cast<float>(j) / static_cast<float>(height - 1);
            Ray r = castRay(u, v);
            if (sphere.intersects(r, t, 0.00001, 100000.0f)){
                const auto normal = glm::normalize(r.at(t) - sphere.center());
                color = r.determineColor(true,  normal, t);
            }else{
                //TODO(threadedstream): this is a pointless action. determineColor already does that
                color = r.defaultColor();
            }
            manipulator.writeSingle(color);
        }
    }
}

void Camera::sampleRayCasting(const int32_t width, const int32_t height) {
    const auto ray_origin = glm::vec3{0.0f, 0.0f, 0.0f};
    Ray r(ray_origin, lower_left_corner_);
    PPManipulator manipulator{"/home/threadedstream/sample.ppm", width, height, 260};
    // TODO(threadedstream): provide better error diagnostic?
    if (!manipulator.handle()) { return; }

    float u{0.0f}, v{0.0f};
    // TODO(threadedstream): consider enabling parallelism by means of OMP extension
    for (int32_t j = height - 1; j >= 0; j--) {
        for (int32_t i = 0; i < width; i++) {
            u = static_cast<float>(i) / static_cast<float>(width - 1);
            v = static_cast<float>(j) / static_cast<float>(height - 1);
            const glm::vec3 ray_color = r.defaultColor();
            manipulator.writeSingle(ray_color);
        }
    }
}

