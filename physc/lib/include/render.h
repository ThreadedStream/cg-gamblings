#pragma once

#include <SDL_image.h>
#include "../include/defs.hpp"


// compute the size of it
class Context {
public:
    Context();

    inline ~Context() noexcept {
        reclaimResources();
    }

    void render(const SDL_Point* draw_points, int count);

    void clearScreen();

    [[nodiscard]] inline SDL_Renderer* context_renderer() const noexcept { return renderer; }
    [[nodiscard]] inline SDL_Window* context_window() const noexcept { return window; }
    [[nodiscard]] inline b2World& contextWorld() noexcept { return world; }

private:
    void reclaimResources();

    void initializeWorld();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    b2World world;
};


