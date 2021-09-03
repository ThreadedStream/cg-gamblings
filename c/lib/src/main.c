#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <sys/timeb.h>
#include <float.h>


#include <SDL2/SDL.h>
#include <SDL_ttf.h>

#include "../include/render.h"
#include "../include/draw.h"
#include "../include/utils.h"
#include "../include/entity.h"
#include "../include/animation.h"
#include "memory.h"

#define DUMMY_CONST 10

char err[512];

#define BENCHMARK_MALLOC(count) \
    for (int i = 0; i < (count); ++i){ \
        void* ptr = malloc(DUMMY_CONST+i); \
        if (!(ptr)) {           \
            sprintf(err, "malloc failed on %d iteration", i); \
            printf("%s", err);  \
            exit(-1);\
        }                                \
        free(ptr); \
    }

typedef int32_t BOOL;
#define FALSE 0 != 0
#define TRUE  1 == 1


// Hacky work-around to generate compile-time errors
// It's very weird that gcc does not generate an error when declaring zero-sized arrays
#define STATIC_ASSERT(condition) char arr[(condition) - 1]


#define MIN(x, y) (x) < (y) ? (x) : (y)

#define RECT_SPEED 150

void monitorCloseEvent(SDL_Event *event, BOOL *running);

void updateHero(struct Entity *entity, SDL_Event *event, BOOL *running, float delta);

int main() {
//
//    pid_t pid = getpid();
//
//    fprintf(stderr, "PID: %d\n", pid);
//
//    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//        printf("failed to initialized video frame");
//        exit(-1);
//    }
//
//    struct ContextGraphique *context = initializeContext();
//
//    SDL_Event event;
//
//    //BOOL running = TRUE;
//
//    Entity hero = {1, "Hero", {30, 30}, loadTexture(context->renderer, "assets/HeroKnight.png")};
//
//    TTF_Font *surumaFont = TTF_OpenFont("/usr/share/fonts/truetype/lato/Lato-Hairline.ttf", 24);
//
//    SDL_Color White = {255, 255, 255};
//
//    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(surumaFont, "Your are fucking looser", White);
//
//    SDL_Texture* Message = SDL_CreateTextureFromSurface(context->renderer, surfaceMessage);
//
//    // https://gafferongames.com/post/fix_your_timestep/
//    float t = 0.0f, dt = 1.0f / 60.0f;
//    int animationFrame = 0, animationStep = 0;
//    clock_t start = clock();
//    BOOL running = TRUE;
//
//    for (; running ;) {
//        clock_t now = clock();
//        float frameTime = (float) (now - start) / (float) CLOCKS_PER_SEC;
//        start = now;
//
//        //monitorCloseEvent(&event, &running);
//        while (frameTime > 0.0) {
//            float delta = MIN(frameTime, dt);
//            frameTime -= delta;
//            t += delta;
//        }
//
//        updateHero(&hero, &event, &running, dt);
//
//        clearScreen(context);
//        animationStep = 100 * (animationFrame % 10);
//        //renderSpriteAt(context->renderer, hero.texture, 0, 0, 50, 55);
//        SDL_Rect srcrect =  {animationStep, 0, 100, 55};
//        SDL_Rect destrect = {0, 0, 100, 55};
//
//        SDL_RenderCopy(context->renderer, hero.texture, &srcrect, &destrect);
//
//        SDL_Rect Message_rect; //create a rect
//        Message_rect.x = 0;  //controls the rect's x coordinate
//        Message_rect.y = 0; // controls the rect's y coordinte
//        Message_rect.w = 100; // controls the width of the rect
//        Message_rect.h = 100; // controls the height of the rect
//
//        SDL_RenderCopy(context->renderer, Message, NULL, &Message_rect);
//        render(context);
//        animationFrame++;
//    }
//
//    reclaimContextResources(context);

    clock_t start = clock();
    BENCHMARK_MALLOC(1000000);
    clock_t end = clock();

    float elapsed = (float) end - (float) start;
    printf("elapsed %f", elapsed);
    return 0;
}

void monitorCloseEvent(SDL_Event *event, BOOL *running) {
    if (SDL_PollEvent(event)) {
        switch (event->type) {
        }
    }
}


void updateHero(struct Entity *entity, SDL_Event *event, BOOL *running, float delta) {
    if (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_KEYDOWN:
                switch (event->key.keysym.scancode) {
                    case SDL_SCANCODE_D:
                        // TODO(threadedstream): resolve a problem with a delta time
                        entity->pos.x += (float) (RECT_SPEED * delta);
                        break;
                    case SDL_SCANCODE_A:
                        entity->pos.x -= (float) (RECT_SPEED * delta);
                        break;
                    case SDL_SCANCODE_W:
                        entity->pos.y -= (float) (RECT_SPEED * delta);
                        break;
                    case SDL_SCANCODE_S:
                        entity->pos.y += (float) (RECT_SPEED * delta);
                        break;
                    default:
                        break;
                }
                break;
            case SDL_WINDOWEVENT:
                switch (event->window.event) {
                    case SDL_WINDOWEVENT_CLOSE:
                        *running = FALSE;
                }
                break;
        }
    }
}



