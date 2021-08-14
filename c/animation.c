#include "animation.h"

void animate(SDL_Renderer *renderer, SDL_Texture *texture, animation_params_t *animParams) {
    static int32_t globalCounter = 0;
    if (animParams->counter == (animParams->inverseFrameSpeed - 1)) {
        animParams->currentFrame = (animParams->currentFrame + 1) % animParams->endFrameX;
        globalCounter += animParams->inverseFrameSpeed;
    }

    animParams->counter = (animParams->counter + 1) % animParams->inverseFrameSpeed;
    SDL_Rect srcrect = {(int) animParams->currentFrame * animParams->width, animParams->animationY * animParams->height, animParams->width,
                        animParams->height};
    SDL_Rect destrect = {20, 20, animParams->width, animParams->height};
    if (animParams->currentFrame == animParams->endFrameX - 1 && globalCounter == animParams->inverseFrameSpeed * (animParams->endFrameX - 1)){
        animParams->animationY = (animParams->animationY + 1) % animParams->endFrameY;
        globalCounter = 0;
    }

    SDL_RenderCopy(renderer, texture, &srcrect, &destrect);
}

//void animationShowcase(SDL_Renderer* renderer, SDL_Texture *texture, animation_params_t *animParams);

