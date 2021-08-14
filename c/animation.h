#ifndef PHYSC_ANIMATION_H
#define PHYSC_ANIMATION_H


#include <SDL_render.h>

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
    // counter determines a space between individual frames
    uint32_t counter;
    // currentFrame determines a frame being played at the moment
    uint32_t currentFrame;
    int32_t  animationY;
}animation_params_t;

void animate(SDL_Renderer* renderer, SDL_Texture* texture,animation_params_t *animParams);

#endif //PHYSC_ANIMATION_H
