#include "../include/utils.h"


void
abnormalExit(struct ContextGraphique *context, const char *message) {
    fputs(message, stderr);
    free(context);
    context = NULL;
    exit(-1);
}


void
reclaimContextResources(struct ContextGraphique *context) {
    SDL_DestroyWindow(context->window);
    context->window = NULL;
    SDL_DestroyRenderer(context->renderer);
    context->renderer = NULL;
    SDL_Quit();
    free(context);
    context = NULL;
}

uint32_t
startsWith(const char* str, const char* pattern){
    //TODO(threadedstream): Possibly, string interning is required
    uint32_t patternLength = strlen(pattern);
    if (strlen(str) < patternLength){
        return -1;
    }

    uint32_t i = 0;
    for (; i < patternLength ; ++i){
        if (str[i] != pattern[i]){
            goto failure;
        }
    }

    success:
    return 1;

    failure:
    return -1;

}

const char*
parentDir(const char* path){
    static char dest[128];

    uint32_t pathLength = strlen(path);
    uint32_t i;
    for (i = pathLength - 1; i > 0, path[i] != '/'; i--);
    if (i == 0) {
        return "";
    }

    substr(path, dest, pathLength, 0, i);

    return dest;
}

void
substr(const char* src, char* dest, uint32_t srcSize, uint32_t start, uint32_t end) {
    uint32_t idx = 0;
    for (;*(src+start) != '\0', start < end; *(dest+idx++) = *(src+start), start++);
}