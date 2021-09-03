#include <SDL_render.h>
#include "defs.h"

#pragma once


typedef struct animation_params_t{
    // inverseFrameSpeed determines how fast the animation should be played
    // as its name implies, large values produce slow animation speed
    uint32_t inverseFrameSpeed;
    // endFrameX determines the number of a last column in a sprite sheet
    uint32_t endFrameX;
    // endFrameY determines the number of a last row in a sprite sheet
    uint32_t endFrameY;
    // width determines the width of a single sprite in a sprite sheet
    int32_t width;
    // height determines the height of a single sprite in a sprite sheet
    int32_t height;
}animation_params_t;

void play(SDL_Renderer* renderer, SDL_Texture* texture,const animation_params_t *animParams);

void animationShowcase(SDL_Renderer* renderer, SDL_Texture *texture,const animation_params_t *animParams);

void addAnimation(const char* animationName, int32_t startingFrameX, int32_t startingFrameY);


