#include "../include/camera.h"
#include "../include/ppm.h"

void Camera::castNumerousRaysIntoScene(const int32_t width,const int32_t height){
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
            Ray r = castRay(u, v);
            const glm::vec3 color = r.determineColor(r, sphere, t);
            manipulator.writeSingle(color);
        }
    }
}
