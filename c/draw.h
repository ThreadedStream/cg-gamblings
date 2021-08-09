#ifndef PHYSC_DRAW_H
#define PHYSC_DRAW_H

#include "render.h"
#include <unistd.h>

SDL_Texture* loadTexture(struct ContextGraphique* context, const char* path);

void blit(struct ContextGraphique* context, SDL_Texture* texture, int x, int y);

void loadTextureAndBlit(struct ContextGraphique* context, const char* path, int x, int y);


#endif //PHYSC_DRAW_H
