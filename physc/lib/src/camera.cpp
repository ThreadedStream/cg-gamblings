#include "../include/camera.h"
#include <include/ppm.h>

#define ENABLE_ANTIALIASING

void
Camera::castNumerousRaysIntoScene(Scene &scene, const char *output_file, const int32_t width, const int32_t height) {
    PPManipulator manipulator{output_file, width, height, 255};
    // TODO(threadedstream): provide an error diagnostic?
    if (!manipulator.handle()) { return; }

    float u{0.0f}, v{0.0f};
    Color color{0.0f, 0.0f, 0.0f};

    HitRecord hit_record{};
#ifdef ENABLE_ANTIALIASING
    const int64_t samples_per_pixel = 4;
#endif

    for (int32_t j = height - 1; j >= 0; j--) {
        for (int32_t i = 0; i < width; i++) {
#ifdef ENABLE_ANTIALIASING
            // antialiasing stage
            for (int64_t curr_sample = 0; curr_sample < samples_per_pixel; curr_sample++) {
                u = static_cast<float>(i + random_double()) / static_cast<float>(width - 1);
                v = static_cast<float>(j + random_double()) / static_cast<float>(height - 1);
                Ray r = castRay(u, v);
                color += r.determineColor(r,scene, 50);
            }
            color /= samples_per_pixel;
            manipulator.writeSingle(color);
            color = {0.0f, 0.0f, 0.0f};
#else
            u = static_cast<float>(i) / static_cast<float>(width - 1);
            v = static_cast<float>(j) / static_cast<float>(height - 1);
            Ray r = castRay(u, v);
            color = r.determineColor(r, scene, 50);
            manipulator.writeSingle(color);
#endif
        }
    }
}

void Camera::sampleRayCasting(const char *output_file, const int32_t width, const int32_t height) {
    const auto ray_origin = glm::vec3{0.0f, 0.0f, 0.0f};
    PPManipulator manipulator{output_file, width, height, 260};
    // TODO(threadedstream): provide better error diagnostic?
    if (!manipulator.handle()) { return; }
    Sphere sphere(glm::vec3{0.0f, 0.0f, -1.0f}, 0.5f);

    HitRecord hit_record{};
    float t;
    glm::vec3 color;

    float u{0.0f}, v{0.0f};
    // TODO(threadedstream): consider enabling parallelism by means of OMP extension
    for (int32_t j = height - 1; j >= 0; j--) {
        for (int32_t i = 0; i < width; i++) {
            u = static_cast<float>(i) / static_cast<float>(width - 1);
            v = static_cast<float>(j) / static_cast<float>(height - 1);
            Ray r = castRay(u, v);
            color = sphere.intersects(r, t, 1e-6, 1e6, hit_record)
                    ? r.defaultColor()
                    : glm::vec3{1.0f, 1.0f, 1.0f};

            manipulator.writeSingle(color);
        }
    }
}


