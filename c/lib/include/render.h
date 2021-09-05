#pragma once

#include <SDL_image.h>
#include "../include/defs.hpp"


// compute the size of it
class Context {
public:
    Context() noexcept;

    inline ~Context() noexcept {
        reclaimResources();
    }

    void render();

    void clearScreen();

    template<class Allocator>
    void begetBox2d();

    [[nodiscard]] inline SDL_Renderer* context_renderer() const noexcept { return renderer; }
    [[nodiscard]] inline SDL_Window* context_window() const noexcept { return window; }

private:
    void reclaimResources();


private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    b2World* world;
};


