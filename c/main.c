#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <sys/timeb.h>

#include "SDL2/source/include/SDL.h"
#include <SDL2/SDL2_gfxPrimitives.h>

#define WIDTH 600
#define HEIGHT 400

typedef int8_t BOOL;
#define FALSE 0 != 0
#define TRUE  1 == 1

typedef struct {
    SDL_Window *window;
    SDL_Surface *window_surface;
    SDL_Renderer *renderer;
} ContextGraphique;

void abnormal_exit(ContextGraphique *context, const char* message){
    fputs(message, stderr);
    free(context);
    context = NULL;
    exit(-1);
}

void reclaim_context_resources(ContextGraphique* context){
    SDL_DestroyWindow(context->window);
    SDL_Quit();
    free(context);
    context = NULL;
}

ContextGraphique* initialize_context() {
    ContextGraphique* context = calloc(1, sizeof(ContextGraphique));
    if (!context){
        fputs("malloc() failed", stderr);
        exit(-1);
    }

    context->window = SDL_CreateWindow("Sample Window",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WIDTH, HEIGHT,
                                       SDL_WINDOW_OPENGL);

    if (!context->window){
        abnormal_exit(context, "failed to initialize a window");
    }

    context->window_surface = SDL_GetWindowSurface(context->window);
    if (!context->window_surface){
        abnormal_exit(context, "failed to initialize a window surface");
    }

    context->renderer = SDL_CreateRenderer(context->window, -1, 0x0);
    if (!context->renderer){
        abnormal_exit(context, "failed to initialize a renderer");
    }


    return context;
}


int main() {
    pid_t pid = getpid();

    fprintf(stderr, "PID: %d", pid);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("failed to initialized video frame");
        exit(-1);
    }

    SDL_Rect rect = {30,30,30, 30};

    ContextGraphique* context = initialize_context();
    SDL_Event event;

    //SDL_SetRenderDrawColor(context->renderer, 255, 255, 0, 255);
    BOOL running = TRUE;
    clock_t delta;

    for (; running ;) {
        clock_t start = clock();

        if (SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_KEYDOWN:
                    switch(event.key.keysym.scancode) {
                        case SDL_SCANCODE_ESCAPE:
                            running = FALSE;
                            break;
                        case SDL_SCANCODE_D:
                            rect.x += (int) (50 * delta);
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_WINDOWEVENT:
                    switch(event.window.event){
                        case SDL_WINDOWEVENT_CLOSE:
                            running = FALSE;
                    }
                    break;
            }
        }

        SDL_RenderFillRect(context->renderer, &rect);

        SDL_FillRect(context->window_surface, &rect, SDL_MapRGB(context->window_surface->format, 80,180,179));
        SDL_FillRect(context->window_surface, NULL, SDL_MapRGB(context->window_surface->format, 65,193,193));

        //SDL_UpdateWindowSurface(context->window);
        SDL_RenderPresent(context->renderer);

        SDL_RenderClear(context->renderer);
        clock_t end = clock();

        //clock_t delta = (end - start) / CLOCKS_PER_SEC;
        fprintf(stderr, "Seconds: %ld ms\n", delta);
    }

    reclaim_context_resources(context);

    return 0;
}
