#pragma once

#include <box2d/box2d.h>
#include <spdlog/spdlog.h>
#include <glm.hpp>
#include <random>
#include "memory.h"

#if defined __GNUC__
#define FORCE_INLINE __attribute__((always_inline))
#elif defined __clang__
#define FORCE_INLINE inline
#endif

#define WIDTH 600
#define HEIGHT 400

using Color = glm::vec3;
using Point3 = glm::vec3;

static const int half_width = WIDTH / 2;
static const int half_height = HEIGHT / 2;

static constexpr float pi = 3.1415926535897932;

[[maybe_unused]] static const auto to_radians = [](float degrees) -> float {
    return (degrees * pi) / 180.0f;
};

static const auto random_double = []() -> double {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
};

static const auto random_double_between = [](double min, double max) -> double {
    return min + (max - min) * random_double();
};

static const auto random_vec3 = [](double min, double max) -> glm::vec3 {
    return glm::vec3{
            random_double_between(min, max),
            random_double_between(min, max),
            random_double_between(min, max)
    };
};

static const auto random_point_in_unit_sphere = [] (int64_t max_iters) -> Point3 {
    while (max_iters--){
        auto pt = random_vec3(-1, 1);
        if (glm::length(pt) >= 1) continue;
        return pt;
    }
    // return origin upon a failure
    return Point3{0.0f, 0.0f, 0.0f};
};

#define MIN(x, y) (x) < (y) ? (x) : (y)

#define RECT_SPEED 150

#define ARE_INHERENT(val1, val2) sizeof(val1) == sizeof(val2)

#define likely(x) __builtin_expect((x), 1)
#define unlikely(x) __builtin_expect((x), 0)
