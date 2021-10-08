#include "../include/animation.h"


void Animation::play(SDL_Renderer *renderer, SDL_Texture *texture, const AnimationParams *animParams) {
}

void Animation::animationShowcase(SDL_Renderer* renderer, SDL_Texture *texture, const AnimationParams *animParams){
    static uint32_t current_frame_x;
    static int32_t current_frame_y, counter;
    if (counter == (animParams->inverse_frame_speed - 1)) {
        current_frame_x = (current_frame_x + 1) % (int32_t) animParams->end_frame_x;
    }

    counter = (counter + 1) % (int32_t) animParams->inverse_frame_speed;
    SDL_Rect src_rect = {(int) current_frame_x * animParams->width, current_frame_y * animParams->height, animParams->width,
                        animParams->height};
    SDL_Rect dest_rect = {20, 20, animParams->width, animParams->height};
    if (current_frame_x == animParams->end_frame_x - 1){
        current_frame_y = (current_frame_y + 1) % (int32_t) animParams->end_frame_y;
        current_frame_x = 0;
    }

    SDL_RenderCopy(renderer, texture, &src_rect, &dest_rect);
}

