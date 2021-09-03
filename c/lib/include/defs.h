#pragma once

#include "../../extern/box2d/include/box2d/box2d.h"
#include <stdint.h>

#define WIDTH 600
#define HEIGHT 400

typedef int32_t BOOL;
#define FALSE 0 != 0
#define TRUE  1 == 1

#define MIN(x, y) (x) < (y) ? (x) : (y)

#define RECT_SPEED 150

#define ARE_INHERENT(val1, val2) sizeof(val1) == sizeof(val2)

#define STATIC_ASSERT(condition) char arr[(condition) - 1];

