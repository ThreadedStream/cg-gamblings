#pragma once

#include "defs.hpp"

class MathUtils{
public:
    // Gaussian elimination for finding inverse of a matrix
    static glm::mat3x3 mat_inverse_3x3(glm::vec3& row1, glm::vec3& row2, glm::vec3& row3) noexcept{
        auto row1_identity = glm::vec3{1, 0, 0};
        auto row2_identity = glm::vec3{0, 1, 0};
        auto row3_identity = glm::vec3{0, 0, 1};
        float current_scalar{0.0f};

        // [2 2 3]
        // [2 3 4]
        // [4 5 6]
        // R1 = R1 / 2
        current_scalar = row1.x;
        row1 /= current_scalar; row1_identity /= current_scalar;

        // R2 = R1 * row2.x - R2
        // R3 = R1 * row3.x - R3
        // [1 a b]
        // [0 c d]
        // [0 e f]
        current_scalar = row2.x;
        row2.x = 0;                                  row2_identity.x = (row1_identity.x * current_scalar) - row2_identity.x;
        row2.y = (row1.y * current_scalar) - row2.y; row2_identity.y = (row1_identity.y * current_scalar) - row2_identity.y;
        row2.z = (row1.z * current_scalar) - row2.z; row2_identity.z = (row1_identity.z * current_scalar) - row2_identity.z;

        // scalar now becomes row3.x
        current_scalar = row3.x;
        row3.x = 0;                                  row3_identity.x = (row1_identity.x * current_scalar) - row3_identity.x;
        row3.y = (row1.y * current_scalar) - row3.y; row3_identity.y = (row1_identity.y * current_scalar) - row3_identity.y;
        row3.z = (row1.z * current_scalar) - row3.z; row3_identity.z = (row1_identity.z * current_scalar) - row3_identity.z;

        // Now, one needs to set c to 1, i.e divide the second row by c;
        current_scalar = row2.y;
        row2 /= current_scalar; row2_identity /= current_scalar;

        // We ended up with a following matrix
        // [1 a b]
        // [0 1 d]
        // [0 e f]

        // Note that even though i didn't change the letters, the numbers have changed.
        // apologies for the laziness

        // Now one should choose second column as a pivot
        // R1 = R2 * row1.y - R1; R3 = R2 * row3.y - R3
        current_scalar = row1.y;
        row1.x = (row2.x * current_scalar) - row1.x; row1_identity.x = (row2_identity.x * current_scalar) - row1_identity.x;
        row1.y = 0;                                  row1_identity.y = (row2_identity.y * current_scalar) - row1_identity.y;
        row1.z = (row2.z * current_scalar) - row1.z; row1_identity.z = (row2_identity.z * current_scalar) - row1_identity.z;

        current_scalar = row3.y;
        row3.x = (row2.x * current_scalar) - row3.x; row3_identity.x = (row2_identity.x * current_scalar) - row3_identity.x;
        row3.y = 0;                                  row3_identity.y = (row2_identity.y * current_scalar) - row3_identity.y;
        row3.z = (row2.z * current_scalar) - row3.z; row3_identity.z = (row2_identity.z * current_scalar) - row3_identity.z;


        // We ended up with a following matrix
        // [1 0 b]
        // [0 1 d]
        // [0 0 f]

        // Setting f to 1, i.e dividing third row by f
        current_scalar = row3.z;
        row3 /= current_scalar; row3_identity /= current_scalar;

        // We ended up with a following matrix
        // [1 0 b]
        // [0 1 d]
        // [0 0 1]

        // Choosing third column as a pivot
        // R2 = R3 * row2.z  - R2; R1 = R3 * row1.z - R1
        current_scalar = row2.z;
        row2.x = (row3.x * current_scalar) - row2.x; row2_identity.x = (row3_identity.x * current_scalar) - row2_identity.x;
        row2.y = (row3.y * current_scalar) - row2.y; row2_identity.y = (row3_identity.y * current_scalar) - row2_identity.y;
        row2.z = (row3.z * current_scalar) - row2.z; row2_identity.z = (row3_identity.z * current_scalar) - row2_identity.z;

        current_scalar = row1.z;
        row1.x = (row3.x * current_scalar) - row1.x; row1_identity.x = (row3_identity.x * current_scalar) - row1_identity.x;
        row1.y = (row3.y * current_scalar) - row1.y; row1_identity.y = (row3_identity.y * current_scalar) - row1_identity.y;
        row1.z = (row3.z * current_scalar) - row1.z; row1_identity.z = (row3_identity.z * current_scalar) - row1_identity.z;

        if (row1.x == -1) {
            current_scalar = -1;
            row1 *= current_scalar; row1_identity *= current_scalar;
        }

        if (row2.y == -1) {
            current_scalar = -1;
            row2 *= current_scalar; row2_identity *= current_scalar;
        }

        if (row3.z == -1) {
            current_scalar = -1;
            row3 *= current_scalar; row3_identity *= current_scalar;
        }

        return glm::transpose(glm::mat3x3{});
    }
};