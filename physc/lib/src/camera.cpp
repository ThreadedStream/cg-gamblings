#include "../include/camera.h"
#include <include/ppm.h>

void Camera::castNumerousRaysIntoScene(Scene& scene, const char *output_file, const int32_t width, const int32_t height) {
    PPManipulator manipulator{output_file, width, height, 255};
    // TODO(threadedstream): provide an error diagnostic?
    if (!manipulator.handle()) { return; }

    float u{0.0f}, v{0.0f};
    glm::vec3 color;

    HitRecord hit_record{};

    const int64_t samples_per_pixel = 50;

    const int64_t size = scene.size();

    const auto hittables = scene.hittables();

    // TODO(threadedstream): Benchmark it
#pragma omp parallel for
    for (int32_t j = height - 1; j >= 0; j--) {
        for (int32_t i = 0; i < width - 1; i++) {
            u = static_cast<float>(i) / static_cast<float>(width - 1);
            v = static_cast<float>(j) / static_cast<float>(height - 1);
            Ray r = castRay(u, v);
            const auto has_intersection = scene.getClosestT(r, hit_record);
            color = r.determineColor(has_intersection, hit_record.normal, hit_record.t);
            manipulator.writeSingle(color);
        }
    }
}

void Camera::sampleRayCasting(const char *output_file, const int32_t width, const int32_t height) {
    const auto ray_origin = glm::vec3{0.0f, 0.0f, 0.0f};
    Ray r(ray_origin, lower_left_corner_);
    PPManipulator manipulator{output_file, width, height, 260};
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


