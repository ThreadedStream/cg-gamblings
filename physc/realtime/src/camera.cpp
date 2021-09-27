#include <include/camera.h>


void Camera::move(float factor, const Direction &dir) noexcept {
    switch (dir) {
        case Direction::FORWARD:
            eye_ += factor * front_;
            break;
        case Direction::BACKWARD:
            eye_ -= factor * front_;
            break;
        case Direction::LEFT:
            eye_ -= glm::normalize(glm::cross(front_, up)) * factor;
            break;
        case Direction::RIGHT:
            eye_ += glm::normalize(glm::cross(front_, up)) * factor;
            break;
        default:
            break;
    }
}