#include "../include/animation.h"




void animate(SDL_Renderer *renderer, SDL_Texture *texture, const animation_params_t *animParams) {
}

void animationShowcase(SDL_Renderer* renderer, SDL_Texture *texture, const animation_params_t *animParams){
    static uint32_t currentFrameX;
    static int32_t currentFrameY, counter;
    if (counter == (animParams->inverseFrameSpeed - 1)) {
        currentFrameX = (currentFrameX + 1) % (int32_t) animParams->endFrameX;
    }

    counter = (counter + 1) % (int32_t) animParams->inverseFrameSpeed;
    SDL_Rect srcrect = {(int) currentFrameX * animParams->width, currentFrameY * animParams->height, animParams->width,
                        animParams->height};
    SDL_Rect destrect = {20, 20, animParams->width, animParams->height};
    if (currentFrameX == animParams->endFrameX - 1){
        currentFrameY = (currentFrameY + 1) % (int32_t) animParams->endFrameY;
        currentFrameX = 0;
    }

    SDL_RenderCopy(renderer, texture, &srcrect, &destrect);
}

