#pragma once

#include <spdlog/spdlog.h>
#include <glm.hpp>
#include <random>
#include <memory>

#if defined __GNUC__
#define FORCE_INLINE __attribute__((always_inline))
#elif defined __clang__
#define FORCE_INLINE inline
#endif

#define WIDTH 600
#define HEIGHT 400

using Color = glm::vec3;
using Point3 = glm::vec3;

enum Colors {
    WHITE,
    BLACK
};

constexpr Color colors[2] = {Color{1.0f, 1.0f, 1.0f},
                             Color{0.0f, 0.0f, 0.0f}};

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

static const auto random_point_in_unit_sphere = []() -> Point3 {
    while (true) {
        auto pt = random_vec3(-1, 1);
        if (glm::length(pt) >= 1) continue;
        return pt;
    }
};

static const auto random_unit_vector = []() -> glm::vec3 {
    return glm::normalize(random_point_in_unit_sphere());
};

static const auto random_in_hemisphere = [](const glm::vec3 &normal) -> glm::vec3 {
    Point3 unit_sphere_pt = random_point_in_unit_sphere();
    if (glm::dot(unit_sphere_pt, normal) > 0)
        return unit_sphere_pt;

    return -unit_sphere_pt;
};

static const auto clamp = [](float value, float min, float max) -> float {
    return value < min ? min : (value > max) ? max : value;
};

static const auto vector_near_zero = [](const glm::vec3 &v, float tolerance) -> bool {
    return (std::fabs(v.x) < tolerance)
           && (std::fabs(v.y) < tolerance)
           && (std::fabs(v.z) < tolerance);
};

#define MIN(x, y) (x) < (y) ? (x) : (y)

#define RECT_SPEED 150

#define likely(x) __builtin_expect((x), 1)
#define unlikely(x) __builtin_expect((x), 0)
