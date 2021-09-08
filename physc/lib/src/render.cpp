#include "../include/render.h"


static SDL_Point draw_points[3] = {
        // Presumably, right-angled triangle
        {half_width, half_height},
        {half_width, half_height + 150},
        {half_width + 150, half_height}
};

Context::Context():
    world(b2Vec2{0, -10.0f}){
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

    // Probably, it's going to rely on default malloc
//    world = static_cast<b2World*>(AllocatorWrapper::getSingleton()->allocate(sizeof(b2World)));
//    if (!world){
//        printf("malloc failed for b2World*");
//        reclaimResources();
//        exit(-1);
//    }
}



void Context::initializeWorld() {
}

void Context::clearScreen() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}

b2World *begetBox2d() {
    // TODO(threadedstream): fill in later
    //b2World world =

    return nullptr;
}

// TODO(threadedstream): how does vptr table work in C++?
void Context::render(const SDL_Point* draw_points, int count) {

    SDL_RenderPresent(renderer);
}

void Context::reclaimResources() {
    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }
    window = nullptr;

    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }
    renderer = nullptr;
}
