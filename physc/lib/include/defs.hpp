#pragma once

#include <box2d/box2d.h>
#include <spdlog/spdlog.h>
#include <glm.hpp>
#include "memory.h"

#if defined __GNUC__
#define FORCE_INLINE __attribute__((always_inline))
#elif defined __clang__
#define FORCE_INLINE inline
#endif

#define WIDTH 600
#define HEIGHT 400

static const int half_width = WIDTH / 2;
static const int half_height = HEIGHT / 2;

static constexpr float pi = 3.1415926535897932;

[[maybe_unused]] static const auto to_radians = [] (float degrees) -> float{
    return (degrees * pi) / 180.0f;
};



#define MIN(x, y) (x) < (y) ? (x) : (y)

#define RECT_SPEED 150

#define ARE_INHERENT(val1, val2) sizeof(val1) == sizeof(val2)

#define likely(x) __builtin_expect((x), 1)
#define unlikely(x) __builtin_expect((x), 0)
