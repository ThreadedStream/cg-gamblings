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

constexpr int32_t WIDTH = 800;
constexpr int32_t HEIGHT = 600;

constexpr int32_t HALF_WIDTH = WIDTH / 2;
constexpr int32_t HALF_HEIGHT = HEIGHT / 2;

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

static constexpr float pi = 3.141592653;

[[maybe_unused]] static const auto to_radians = [](float degrees) -> float {
    return (degrees * pi) / 180.0f;
};


// NOTE(threadedstream): for now, we assume that T is float or double
template<typename T>
static const auto random_real_number = []() -> T {
    static std::uniform_real_distribution<T> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
};

template<typename T>
static const auto random_real_between = [](T min, T max) -> T {
    return min + (max - min) * random_real_number<T>();
};

template <typename T>
static const auto random_vec3 = [](T min, T max) -> glm::vec3 {
    return glm::vec3{
            random_real_between<T>(min, max),
            random_real_between<T>(min, max),
            random_real_between<T>(min, max)
    };
};

static const auto random_point_in_unit_sphere = []() -> Point3 {
    while (true) {
        auto pt = random_vec3<float>(-1, 1);
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

#define RECT_SPEED 150

#define likely(x) __builtin_expect((x), 1)
#define unlikely(x) __builtin_expect((x), 0)
