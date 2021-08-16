#ifndef PHYSC_DEFS_H
#define PHYSC_DEFS_H

#define WIDTH 600
#define HEIGHT 400

typedef int32_t BOOL;
#define FALSE 0 != 0
#define TRUE  1 == 1

#define MIN(x, y) (x) < (y) ? (x) : (y)

#define RECT_SPEED 150

#define ARE_INHERENT(val1, val2) sizeof(val1) == sizeof(val2)

#define STATIC_ASSERT(condition) char arr[(condition) - 1];

#endif //PHYSC_DEFS_H
