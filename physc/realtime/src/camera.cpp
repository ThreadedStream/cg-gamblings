#include <include/camera.h>
#include <spdlog/spdlog.h>

void Camera::move(float factor, const Direction &dir) noexcept {
    switch (dir) {
        case Direction::FORWARD:
            eye_ += factor * front_;
            break;
        case Direction::BACKWARD:
            eye_ -= factor * front_;
            break;
        case Direction::LEFT:
            right_ = glm::normalize(glm::cross(front_, up_));
            eye_ -= right_ * factor;
            break;
        case Direction::RIGHT:
            right_ = glm::normalize(glm::cross(front_, up_));
            eye_ += right_ * factor;
            break;
        default:
            break;
    }
}

void Camera::rotate(double x_pos, double y_pos, float dt, bool &initial) {

    // disable "unused" warnings
    (void)dt;
}
