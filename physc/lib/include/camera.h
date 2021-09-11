#pragma once

#include "ray.h"

class Camera{
public:
    explicit Camera(const int32_t width, const int32_t height) {
        setup(width, height);
    }

    [[nodiscard]] inline Ray castRay(const float u, const float v) {
        return Ray(origin_, lower_left_corner_ + u * horizontal_ + v * vertical_ - origin_);
    }

    void castNumerousRaysIntoScene(const int32_t width,const int32_t height);

    void sampleRayCasting(int32_t width, int32_t height);

private:
    void setup(const int32_t width, const int32_t height) {
        aspect_ratio_ = static_cast<float>(width) / static_cast<float>(height);

        viewport_height_ = 2.0;
        viewport_width_ = aspect_ratio_ * viewport_height_;
        focal_length_ = 1.0;

        origin_ = glm::vec3{0, 0, 0};
        horizontal_ = glm::vec3{viewport_width_, 0.0f, 0.0f};
        vertical_ = glm::vec3{0.0f, viewport_height_, 0.0f};
        lower_left_corner_ =
                origin_ - (horizontal_ / 2.0f) - (vertical_ / 2.0f) - glm::vec3(0, 0, focal_length_);
    }
private:
    float aspect_ratio_;
    float viewport_height_;
    float viewport_width_;
    float focal_length_;
    glm::vec3 origin_;
    glm::vec3 horizontal_;
    glm::vec3 vertical_;
    glm::vec3 lower_left_corner_;
};