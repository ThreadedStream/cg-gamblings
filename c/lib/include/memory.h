#pragma once

#include <stdint.h>

void *fixed_alloc(int64_t size, int64_t alignment);

void fixed_dealloc(void* ptr, int64_t alignment);


