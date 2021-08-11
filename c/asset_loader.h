#ifndef PHYSC_ASSET_LOADER_H
#define PHYSC_ASSET_LOADER_H

#include "SDL_render.h"
#include "utils.h"

static SDL_Texture* loadTexture(SDL_Renderer *renderer, const char* path) {
    static char buffer[128];

    memset(buffer, 0, sizeof(buffer));

    getcwd(buffer, sizeof(buffer));
    sprintf(buffer, "%s/%s", parentDir(buffer), path);


    return IMG_LoadTexture(renderer, buffer);
}



#endif //PHYSC_ASSET_LOADER_H
