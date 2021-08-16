#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <sys/timeb.h>
#include <float.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "render.h"
#include "draw.h"
#include "utils.h"
#include "entity.h"
#include "animation.h"
#include "defs.h"
#include "map.h"

void monitorCloseEvent(SDL_Event *event, BOOL *running);

void updateHero(struct Entity *entity, SDL_Event *event, BOOL *running, float delta);

int main() {
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
//    int32_t x = 53;
//    int32_t y = 55;
//    int32_t result = ARE_INHERENT(x, y);
//
//    void* type = typeof(int*);
//    //BOOL running = TRUE;
//
//    Entity hero = {1, "Hero", {30, 30}, loadTexture(context->renderer, "assets/HeroKnight.png")};
//
//    // https://gafferongames.com/post/fix_your_timestep/
//    float t = 0.0f, dt = 1.0f / 60.0f;
//
//    clock_t start = clock();
//    BOOL running = TRUE;
//    uint32_t seconds = 0;
//    animation_params_t  idleAnimParams = {200, 8, 10, 100, 55};
//    int animationStep = 100;
//    for (; running;) {
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
//        clearScreen(context);
//
//        uint32_t millis = SDL_GetTicks();
//        seconds = millis / 1000;
//        animationShowcase(context->renderer, hero.texture, &idleAnimParams);
//        render(context);
//    }
//
//    reclaimContextResources(context);

    testHash();

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



