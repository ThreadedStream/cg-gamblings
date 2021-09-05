#include "../include/render.h"


Context::Context() noexcept {
    char err[512];

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    window = SDL_CreateWindow("Sample Window",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WIDTH, HEIGHT,
                                       SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

    if (!window) {
        sprintf(err, "%s\n", SDL_GetError());
        exit(-1);
    }


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        sprintf(err, "%s\n", SDL_GetError());
        reclaimResources();
        exit(-1);
    }
}



void Context::clearScreen() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}

b2World* begetBox2d(){
    // TODO(threadedstream): fill in later
    //b2World world =

    return nullptr;
}

// TODO(threadedstream): how does vptr table work in C++?
void Context::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(renderer, 200, 200, 500, 500);
    SDL_RenderPresent(renderer);
}

void Context::reclaimResources(){
    if (window != nullptr){
        SDL_DestroyWindow(window);
    }
    window = nullptr;

    if (renderer != nullptr){
        SDL_DestroyRenderer(renderer);
    }
    renderer = nullptr;
}
