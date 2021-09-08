#include "render.h"

#pragma once

class Drawing final {
public:
    void blit(Context* context, SDL_Texture* texture, int x, int y);

    void loadTextureAndBlit(Context* context, const char* path, int x, int y);

    // "random" is obviously misplaced
    SDL_Point* randomTriangleData();

    SDL_Point* drawCircle(SDL_Renderer* renderer, int32_t a, int32_t b, int32_t rad);

    void applyTransform(const b2Vec2* points);
};




