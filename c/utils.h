#ifndef PHYSC_UTILS_H
#define PHYSC_UTILS_H

#include "render.h"
#include <string.h>


void abnormalExit(struct ContextGraphique* context, const char* error);

//TODO(threadedstream): Move it to memory.h
void reclaimContextResources(struct ContextGraphique *context);

uint32_t startsWith(const char* str, const char* pattern);

const char* parentDir(const char* path);

void substr(const char* src, char* dest, uint32_t srcSize, uint32_t start, uint32_t end);
#endif //PHYSC_UTILS_H
