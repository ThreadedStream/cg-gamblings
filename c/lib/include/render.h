#pragma once

#include <SDL_image.h>
#include "utils.h"


typedef struct ContextGraphique {
    SDL_Window *window;
    SDL_Renderer *renderer;
} ContextGraphique;


struct ContextGraphique *initializeContext();

void render(struct ContextGraphique *context);

void clearScreen(struct ContextGraphique *context);

void begetBox2d();



