#pragma once

#include "ray.h"
#include "scene.h"

class Camera{
public:
    explicit Camera(const float aspect_ratio,
                    const float vfov) {
        setup(aspect_ratio, vfov);
    }

    [[nodiscard]] inline Ray castRay(const float u, const float v) {
        return Ray(origin_, lower_left_corner_ + (u * horizontal_) + (v * vertical_) - origin_);
    }

    void castNumerousRaysIntoScene(Scene& scene, const char* output_file, int32_t width, int32_t height);

    void sampleRayCasting(const char* output_file, int32_t width, int32_t height);

private:
    void setup(const float aspect_ratio, const float vfov) {
        const float theta_over_two = to_radians(vfov) / 2;
        const float h = std::tan(theta_over_two);
        const float viewport_height_ = 2.0f * h;
        const float viewport_width_ = aspect_ratio * viewport_height_;

        const float focal_length = 1.0;

        origin_ = glm::vec3{0, 0, 0};
        horizontal_ = glm::vec3{viewport_width_, 0.0f, 0.0f};
        vertical_ = glm::vec3{0.0f, viewport_height_, 0.0f};
        lower_left_corner_ =
                origin_ - (horizontal_ / 2.0f) - (vertical_ / 2.0f) - glm::vec3(0, 0, focal_length);
    }
private:
    glm::vec3 origin_;
    glm::vec3 horizontal_;
    glm::vec3 vertical_;
    glm::vec3 lower_left_corner_;
};