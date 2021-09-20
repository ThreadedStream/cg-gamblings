#pragma once

#include "../../shared/defs.hpp"

class MathUtils{
public:
    static glm::mat3x3 mat_inverse_3x3(const glm::vec3& row1, const glm::vec3& row2, const glm::vec3& row3) noexcept{
        auto row1_identity = glm::vec3{1.0f, 0.0f, 0.0f};
        auto row2_identity = glm::vec3{0.0f, 1.0f, 0.0f};
        auto row3_identity = glm::vec3{0.0f, 0.0f, 1.0f};

        // pivotize the first row
        row1 /= row1.x; row1_identity /= row1.x;


    }
};