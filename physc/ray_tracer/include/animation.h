#include <SDL_render.h>
#include "../../shared/defs.hpp"

#pragma once


struct AnimationParams{
    // inverseFrameSpeed determines how fast the animation should be played
    // as its name implies, large values produce slow animation speed
    uint32_t inverse_frame_speed;
    // endFrameX determines the number of a last column in a sprite sheet
    uint32_t end_frame_x;
    // endFrameY determines the number of a last row in a sprite sheet
    uint32_t end_frame_y;
    // width determines the width of a single sprite in a sprite sheet
    int32_t width;
    // height determines the height of a single sprite in a sprite sheet
    int32_t height;
};

class Animation {
public:
    void play(SDL_Renderer* renderer, SDL_Texture* texture,const AnimationParams *anim_params);

    void animationShowcase(SDL_Renderer* renderer, SDL_Texture *texture,const AnimationParams *anim_params);

    void addAnimation(const char* animation_name, int32_t starting_frame_x, int32_t starting_frame_y);
};



