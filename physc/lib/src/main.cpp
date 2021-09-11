#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <sys/timeb.h>

#include <SDL2/SDL.h>

#include "../include/render.h"
#include "../include/draw.h"
#include "../include/ray.h"
#include "../include/sphere.h"
#include "../include/camera.h"

char err[512];


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

    Context context;

    Drawing drawing;

    SDL_Event event;

    bool running = true;

    // https://gafferongames.com/post/fix_your_timestep/
    float t = 0.0f, dt = 1.0f / 60.0f;
    int animationFrame = 0, animationStep = 0;

    //auto triangle_data = drawing.randomTriangleData();
    b2Vec2 box_pos{half_width + 10, half_height};

    SDL_Rect box = {
         .x = static_cast<int32_t>(box_pos.x),
         .y = static_cast<int32_t>(box_pos.y),
         .w = static_cast<int32_t>(50),
         .h = static_cast<int32_t>(50),
    };

    Camera camera(1200, 600);
    Sphere sphere {glm::vec3{100, 10, 100}, 25};

    camera.castNumerousRaysIntoScene(1200, 600);

    for (; running ;) {
        clock_t start = clock();

        monitorCloseEvent(&event, &running);
        context.clearScreen();
        animationStep = 100 * (animationFrame % 10);
        drawing.drawCircle(context.context_renderer(), half_width, half_height, 20);
        SDL_SetRenderDrawColor(context.context_renderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(context.context_renderer(), &box);
        SDL_RenderPresent(context.context_renderer());

        animationFrame++;
        clock_t end = clock();
        auto elapsed = static_cast<float>(end - start) / static_cast<float>(CLOCKS_PER_SEC);
        float fps = 1 / elapsed;
        printf("elapsed: %f, fps: %.2f\n", elapsed, fps);
    }

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
