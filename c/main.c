#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <sys/timeb.h>
#include <float.h>

#include <SDL2/SDL.h>

#include "render.h"
#include "draw.h"
#include "utils.h"
#include "entity.h"
#include "animation.h"


typedef int32_t BOOL;
#define FALSE 0 != 0
#define TRUE  1 == 1

#define MIN(x, y) (x) < (y) ? (x) : (y)

#define RECT_SPEED 150

void monitorCloseEvent(SDL_Event *event, BOOL *running);

void updateHero(struct Entity *entity, SDL_Event *event, BOOL *running, float delta);

int main() {
    pid_t pid = getpid();

    fprintf(stderr, "PID: %d\n", pid);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("failed to initialized video frame");
        exit(-1);
    }

    struct ContextGraphique *context = initializeContext();

    SDL_Event event;

    //BOOL running = TRUE;

    Entity hero = {1, "Hero", {30, 30}, loadTexture(context->renderer, "assets/HeroKnight.png")};

    // https://gafferongames.com/post/fix_your_timestep/
    float t = 0.0f, dt = 1.0f / 60.0f;

    clock_t start = clock();
    BOOL running = TRUE;

    for (; running ;) {
        clock_t now = clock();
        float frameTime = (float) (now - start) / (float) CLOCKS_PER_SEC;
        start = now;

        //monitorCloseEvent(&event, &running);
        while (frameTime > 0.0) {
            float delta = MIN(frameTime, dt);
            frameTime -= delta;
            t += delta;
        }

        updateHero(&hero, &event, &running, dt);
        clearScreen(context);

        uint32_t seconds = (SDL_GetTicks() / 1000) % 10;
        //renderSpriteAt(context->renderer, hero.texture, 0, 0, 50, 55);
        SDL_Rect srcrect = {0, 0, 100, 55};
        SDL_Rect destrect = {seconds, 0, 100, 55};
        SDL_RenderCopy(context->renderer, hero.texture, &srcrect, &destrect);

        render(context);
    }

    reclaimContextResources(context);

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



