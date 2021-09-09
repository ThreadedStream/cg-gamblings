#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <sys/timeb.h>
#include <float.h>


#include <SDL2/SDL.h>

#include "../include/render.h"
#include "../include/draw.h"
#include "../include/entity.h"
#include "../include/animation.h"
#include "../include/memory.h"

#define DUMMY_CONST 10

char err[512];

static SDL_Point draw_points[3] = {
        {150, 150},
        {150, 200},
        {200, 150}
};

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

    AllocatorWrapper allocator_wrapper;

    pid_t pid = getpid();

    fprintf(stderr, "PID: %d\n", pid);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("failed to initialized video frame");
        exit(-1);
    }

    auto context_size = sizeof(Context);
    Context context;

    Drawing drawing;

    SDL_Event event;

    bool running = true;

    SDL_Color white_color = {255, 255, 255};

    // https://gafferongames.com/post/fix_your_timestep/
    float t = 0.0f, dt = 1.0f / 60.0f;
    int animationFrame = 0, animationStep = 0;
    clock_t start = clock();

    //auto triangle_data = drawing.randomTriangleData();
    b2Vec2 box_pos{half_width + 10, half_height};

    SDL_Rect box;

    box.x = static_cast<int32_t>(box_pos.x);
    box.y = static_cast<int32_t>(box_pos.y);

    box.w = static_cast<int32_t>(50);
    box.h = static_cast<int32_t>(50);


    drawing.drawCircle(context.context_renderer(), half_width, half_height, 20);

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
        context.clearScreen();
        animationStep = 100 * (animationFrame % 10);
//        renderSpriteAt(context->context_renderer(), hero.texture, 0, 0, 50, 55);
        SDL_Rect src_rect =  {animationStep, 0, 100, 55};
        SDL_Rect dest_rect = {0, 0, 100, 55};

        //SDL_RenderCopy(context->context_renderer(), hero.texture, &srcrect, &destrect);

//        SDL_SetRenderDrawColor(context.context_renderer(), 255, 255, 0, SDL_ALPHA_OPAQUE);
//        SDL_RenderDrawPoints(context.context_renderer(), circle_data, 112);
        SDL_SetRenderDrawColor(context.context_renderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(context.context_renderer(), &box);
        SDL_RenderPresent(context.context_renderer());

        SDL_Rect message_rect; //create a rect
        message_rect.x = 0;  //controls the rect's x coordinate
        message_rect.y = 0; // controls the rect's y coordinate
        message_rect.w = 100; // controls the width of the rect
        message_rect.h = 100; // controls the height of the rect


        animationFrame++;
    }

    //free(circle_data);
}


void monitorCloseEvent(SDL_Event *event, bool *running) {
    if (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_KEYDOWN:
                switch (event->key.keysym.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        *running = false;
                    default:
                        return;
                }
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



