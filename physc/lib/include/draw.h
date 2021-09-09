#include "render.h"
#include "circle.h"


#pragma once


class Drawing final {
public:
    void blit(Context* context, SDL_Texture* texture, int x, int y);

    void loadTextureAndBlit(Context* context, const char* path, int x, int y);

    // "random" is obviously misplaced
    SDL_Point* randomTriangleData();

    template<class Algorithm = Circle::MidPointAlgorithm>
    void drawCircle(SDL_Renderer* renderer, int32_t x0, int32_t y0, int32_t rad) {
        Circle circle(x0, y0, rad);
        circle.generate<Algorithm>(x0, y0, rad);
    }

    void applyTransform(const b2Vec2* points);


};




