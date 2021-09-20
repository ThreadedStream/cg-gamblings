#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <sys/timeb.h>

// TODO(threadedstream): make the SDL a part of extern folder, as it greatly aids in portability
#include <SDL2/SDL.h>

#include "../include/render.h"
#include "../include/draw.h"
#include "../include/ray.h"
#include "../include/plane.h"
#include "../include/camera.h"
#include "../include/scene.h"
#include "../include/material.h"
#include "../include/math_utils.h"

#include <memory>


char err[512];


#define RECT_SPEED 150


void monitorCloseEvent(SDL_Event *event, bool *running);

void handleInput(struct Entity *entity, SDL_Event *event, bool *running, float delta);


int main(int argc, const char *argv[]) {

    AllocatorWrapper allocator_wrapper;

    pid_t pid = getpid();

    spdlog::info("PID: {}\n", pid);

#if 0
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("failed to initialized video frame");
        exit(-1);
    }
#endif

//    Context context;
//
//    Drawing drawing;
//
//    SDL_Event event;
//
//    bool running = true;
//
//    // https://gafferongames.com/post/fix_your_timestep/
//    float t = 0.0f, dt = 1.0f / 60.0f;
//    int animationFrame = 0, animationStep = 0;
//
//    //auto triangle_data = drawing.randomTriangleData();
//    b2Vec2 box_pos{half_width + 10, half_height};
//
//    SDL_Rect box = {
//            .x = static_cast<int32_t>(box_pos.x),
//            .y = static_cast<int32_t>(box_pos.y),
//            .w = static_cast<int32_t>(50),
//            .h = static_cast<int32_t>(50),
//    };

    Scene scene;

    //TODO(threadedstream): causes problem when used along with a second (huge-ass) sphere
    auto material_ground = std::make_shared<Lambertian>(Color{0.8, 0.8, 0.0});
    auto material_center = std::make_shared<Lambertian>(Color{0.7, 0.3, 0.3});
    auto material_left = std::make_shared<Metal>(Color{0.8, 0.8, 0.8});
    auto material_right = std::make_shared<Metal>(Color{0.8, 0.6, 0.2});

    //TODO(threadedstream): how can i effectively use raw pointers without causing
    // any harm to an overall program's state? I mean, shared_ptrs are not present
    // in C api, and yet somehow developers deal with this memory ownership
    // problem. So, it must be noted that before using any "smarty-pointer" stuff
    // i should thoroughly investigate the problem and find an appropriate solution.
    // That way the intuition behind using shared_ptrs is gained. I don't desire to
    // blindly follow the rules dictated by C++ committee -- that's not right

    //The only thing i grasped during inspecting source code of shared_ptr is that
    // it applies move semantic upon deleter (function pointer to deletion of an object)

    Camera camera(800.0f / 600.0f, 90.0f);
    Sphere sphere1{Point3{0, 0, -1.0f}, 0.5f, material_ground};
    Sphere sphere2{Point3{0.0f, -100.5f, -1.0f}, 100.0f, material_center};
    Sphere sphere3{Point3{-1.0f, 0.0f, -1.0f}, 0.5f, material_left};
    Sphere sphere4{Point3{1.0f, 0.0f, -1.0f}, 0.5f, material_right};


    scene.addObject(&sphere1);
    scene.addObject(&sphere2);
    scene.addObject(&sphere3);
    scene.addObject(&sphere4);

    camera.castNumerousRaysIntoScene(scene, "/home/threadedstream/sample.ppm", 800, 600);

#if 0
    const auto mat = glm::mat3x3{
            {1, 2, 3},
            {4, 5, 6},
            {8, 9, 11}
    };

    const auto transposed_mat = glm::transpose(mat);

    const float det = glm::determinant(mat);
    const float transposed_det = glm::determinant(transposed_mat);

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
    }
#endif
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
