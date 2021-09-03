#include "../include/render.h"

#include "../include/defs.h"

struct ContextGraphique *initializeContext() {
    char err[512];

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    struct ContextGraphique *context = calloc(1, sizeof(struct ContextGraphique));
    if (!context) {
        fputs("malloc() failed\n", stderr);
        exit(-1);
    }

    context->window = SDL_CreateWindow("Sample Window",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WIDTH, HEIGHT,
                                       SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

    if (!context->window) {
        sprintf(err, "%s\n", SDL_GetError());
        abnormalExit(context, err);
    }


    context->renderer = SDL_CreateRenderer(context->window, -1, SDL_RENDERER_ACCELERATED);

    if (!context->renderer) {
        sprintf(err, "%s\n", SDL_GetError());
        abnormalExit(context, err);
    }

    return context;
}


void clearScreen(struct ContextGraphique *context) {
    SDL_SetRenderDrawColor(context->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(context->renderer);
}

void begetBox2d(){

}


void render(struct ContextGraphique *context) {
    SDL_SetRenderDrawColor(context->renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(context->renderer, 200, 200, 500, 500);
    SDL_RenderPresent(context->renderer);
}
