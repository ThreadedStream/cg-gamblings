#ifndef PHYSC_RENDER_H
#define PHYSC_RENDER_H

#include <SDL_image.h>
#include "utils.h"

#define WIDTH 600
#define HEIGHT 400


typedef struct ContextGraphique {
    SDL_Window *window;
    SDL_Renderer *renderer;
} ContextGraphique;


struct ContextGraphique *initializeContext();

void render(struct ContextGraphique *context);

void clearScreen(struct ContextGraphique *context);


#endif //PHYSC_RENDER_H
