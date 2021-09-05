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
#include "../include/entity.h"
#include "../include/animation.h"
#include "../include/b2_allocator.h"
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


#define MIN(x, y) (x) < (y) ? (x) : (y)

#define RECT_SPEED 150

void monitorCloseEvent(SDL_Event *event, bool *running);

void handleInput(struct Entity *entity, SDL_Event *event, bool *running, float delta);

int main(int argc, const char* argv[]) {

    pid_t pid = getpid();

    fprintf(stderr, "PID: %d\n", pid);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("failed to initialized video frame");
        exit(-1);
    }


    Context *context = static_cast<Context*>(B2Allocator::allocate<sizeof(Context)>());

    SDL_Event event;

    bool running = true;

//    Entity hero = {1, "Hero", {30, 30}, loadTexture(context->context_renderer(), "assets/HeroKnight.png")};

    TTF_Font *surumaFont = TTF_OpenFont("/usr/share/fonts/truetype/lato/Lato-Hairline.ttf", 24);

    SDL_Color White = {255, 255, 255};

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(surumaFont, "Your are fucking looser", White);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(context->context_renderer(), surfaceMessage);

    // https://gafferongames.com/post/fix_your_timestep/
    float t = 0.0f, dt = 1.0f / 60.0f;
    int animationFrame = 0, animationStep = 0;
    clock_t start = clock();

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

    //    updateHero(&hero, &event, &running, dt);

        monitorCloseEvent(&event, &running);
        context->clearScreen();
        animationStep = 100 * (animationFrame % 10);
//        renderSpriteAt(context->context_renderer(), hero.texture, 0, 0, 50, 55);
        SDL_Rect src_rect =  {animationStep, 0, 100, 55};
        SDL_Rect dest_rect = {0, 0, 100, 55};

        //SDL_RenderCopy(context->context_renderer(), hero.texture, &srcrect, &destrect);

        SDL_Rect message_rect; //create a rect
        message_rect.x = 0;  //controls the rect's x coordinate
        message_rect.y = 0; // controls the rect's y coordinte
        message_rect.w = 100; // controls the width of the rect
        message_rect.h = 100; // controls the height of the rect

        SDL_RenderCopy(context->context_renderer(), texture, NULL, &message_rect);
        context->render();
        animationFrame++;
    }

    delete context;

}


void monitorCloseEvent(SDL_Event *event, bool *running) {
    if (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_WINDOWEVENT:
                switch (event->window.event) {
                    case SDL_WINDOWEVENT_CLOSE:
                        *running = false;
                }
                break;
        }
    }
}


void handleInput(struct Entity *entity, SDL_Event *event, BOOL *running, float delta) {
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



