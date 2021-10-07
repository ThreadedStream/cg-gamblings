#pragma once

#include <glm.hpp>
#include <shared/defs.hpp>

static constexpr float textured_triangle_vertices[] = {
        // positions          // colors                 // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, /*red*/     1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, /*green*/  1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // top left
};


static constexpr int32_t textured_triangle_indices[] = {
        0, 1, 3,
        1, 2, 3
};


// TODO(threadedstream): try soa
struct SimpleVertex {
    glm::vec3 position; // 12
    glm::vec2 tex_coords; // 8
};

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
} __attribute__((packed));


//static constexpr SampleSceneVertex vertices[] = {
//        {glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 0.0f}},
//        {glm::vec3{0.5f, -0.5f, -0.5f},  glm::vec2{1.0f, 0.0f}},
//};

static constexpr float column_wise_vertices[] = {
        -0.5f, 0.5, 0.5f, 1.0f, 2.0f,
        -0.5f, 0.5, 2.0f, 0.0f, 1.0f
};

// NOTE(threadedstream): when casting SampleSceneVertex[] to float*
// one might notice an interesting "column-wise" way items are laid out in memory.
// so, it will be laid out in the following way
// x x x x x x x x x x x x x x x y y y y y y y y y y y y y z z z z z z z z z z z  and so on
static constexpr SimpleVertex textured_cube_vertices[] = {
        {glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 0.0f}},
        {glm::vec3{0.5f, -0.5f, -0.5f},  glm::vec2{1.0f, 0.0f}},
        {glm::vec3{0.5f, 0.5f, -0.5f},   glm::vec2{1.0f, 1.0f}},
        {glm::vec3{0.5f, 0.5f, -0.5f},   glm::vec2{1.0f, 1.0f}},
        {glm::vec3{-0.5f, 0.5f, -0.5f},  glm::vec2{0.0f, 1.0f}},
        {glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 0.0f}},

        {glm::vec3{-0.5f, -0.5f, 0.5f},  glm::vec2{0.0f, 0.0f}},
        {glm::vec3{0.5f, -0.5f, 0.5f},   glm::vec2{1.0f, 0.0f}},
        {glm::vec3{0.5f, 0.5f, 0.5f},    glm::vec2{1.0f, 1.0f}},
        {glm::vec3{0.5f, 0.5f, 0.5f},    glm::vec2{1.0f, 1.0f}},
        {glm::vec3{-0.5f, 0.5f, 0.5f},   glm::vec2{0.0f, 1.0f}},
        {glm::vec3{-0.5f, -0.5f, 0.5f},  glm::vec2{0.0f, 0.0f}},

        {glm::vec3{-0.5f, 0.5f, 0.5f},   glm::vec2{1.0f, 0.0f}},
        {glm::vec3{-0.5f, 0.5f, -0.5f},  glm::vec2{1.0f, 1.0f}},
        {glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 1.0f}},
        {glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 1.0f}},
        {glm::vec3{-0.5f, -0.5f, 0.5f},  glm::vec2{0.0f, 0.0f}},
        {glm::vec3{-0.5f, 0.5f, 0.5f},   glm::vec2{1.0f, 0.0f}},

        {glm::vec3{0.5f, 0.5f, 0.5f},    glm::vec2{1.0f, 0.0f}},
        {glm::vec3{0.5f, 0.5f, -0.5f},   glm::vec2{1.0f, 1.0f}},
        {glm::vec3{0.5f, -0.5f, -0.5f},  glm::vec2{0.0f, 1.0f}},
        {glm::vec3{0.5f, -0.5f, -0.5f},  glm::vec2{0.0f, 1.0f}},
        {glm::vec3{0.5f, -0.5f, 0.5f},   glm::vec2{0.0f, 0.0f}},
        {glm::vec3{0.5f, 0.5f, 0.5f},    glm::vec2{1.0f, 0.0f}},

        {glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 1.0f}},
        {glm::vec3{0.5f, -0.5f, -0.5f},  glm::vec2{1.0f, 1.0f}},
        {glm::vec3{0.5f, -0.5f, 0.5f},   glm::vec2{1.0f, 0.0f}},
        {glm::vec3{0.5f, -0.5f, 0.5f},   glm::vec2{1.0f, 0.0f}},
        {glm::vec3{-0.5f, -0.5f, 0.5f},  glm::vec2{0.0f, 0.0f}},
        {glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 1.0f}},

        {glm::vec3{-0.5f, 0.5f, -0.5f},  glm::vec2{0.0f, 1.0f}},
        {glm::vec3{0.5f, 0.5f, -0.5f},   glm::vec2{1.0f, 1.0f}},
        {glm::vec3{0.5f, 0.5f, 0.5f},    glm::vec2{1.0f, 0.0f}},
        {glm::vec3{0.5f, 0.5f, 0.5f},    glm::vec2{1.0f, 0.0f}},
        {glm::vec3{-0.5f, 0.5f, 0.5f},   glm::vec2{0.0f, 0.0f}},
        {glm::vec3{-0.5f, 0.5f, -0.5f},  glm::vec2{0.0f, 1.0f}}
};

static constexpr Vertex colored_cube_vertices[] = {
        {glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec3{0.0f, 0.0f, 0.0f}},
        {glm::vec3{0.5f, -0.5f, -0.5f},  glm::vec3{1.0f, 0.0f, 1.0f}},
        {glm::vec3{0.5f, 0.5f, -0.5f},   glm::vec3{1.0f, 1.0f,1.0f}},
        {glm::vec3{0.5f, 0.5f, -0.5f},   glm::vec3{1.0f, 1.0f,1.0f}},
        {glm::vec3{-0.5f, 0.5f, -0.5f},  glm::vec3{0.0f, 1.0f,1.0f}},
        {glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec3{0.0f, 0.0f,1.0f}},

        {glm::vec3{-0.5f, -0.5f, 0.5f},  glm::vec3{0.0f, 0.0f,1.0f}},
        {glm::vec3{0.5f, -0.5f, 0.5f},   glm::vec3{1.0f, 0.0f,1.0f}},
        {glm::vec3{0.5f, 0.5f, 0.5f},    glm::vec3{1.0f, 1.0f,1.0f}},
        {glm::vec3{0.5f, 0.5f, 0.5f},    glm::vec3{1.0f, 1.0f,1.0f}},
        {glm::vec3{-0.5f, 0.5f, 0.5f},   glm::vec3{0.0f, 1.0f,1.0f}},
        {glm::vec3{-0.5f, -0.5f, 0.5f},  glm::vec3{0.0f, 0.0f,1.0f}},

        {glm::vec3{-0.5f, 0.5f, 0.5f},   glm::vec3{1.0f, 0.0f,1.0f}},
        {glm::vec3{-0.5f, 0.5f, -0.5f},  glm::vec3{1.0f, 1.0f,1.0f}},
        {glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec3{0.0f, 1.0f,1.0f}},
        {glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec3{0.0f, 1.0f,1.0f}},
        {glm::vec3{-0.5f, -0.5f, 0.5f},  glm::vec3{0.0f, 0.0f,1.0f}},
        {glm::vec3{-0.5f, 0.5f, 0.5f},   glm::vec3{1.0f, 0.0f,1.0f}},

        {glm::vec3{0.5f, 0.5f, 0.5f},    glm::vec3{1.0f, 0.0f,1.0f}},
        {glm::vec3{0.5f, 0.5f, -0.5f},   glm::vec3{1.0f, 1.0f,1.0f}},
        {glm::vec3{0.5f, -0.5f, -0.5f},  glm::vec3{0.0f, 1.0f,1.0f}},
        {glm::vec3{0.5f, -0.5f, -0.5f},  glm::vec3{0.0f, 1.0f,1.0f}},
        {glm::vec3{0.5f, -0.5f, 0.5f},   glm::vec3{0.0f, 0.0f,1.0f}},
        {glm::vec3{0.5f, 0.5f, 0.5f},    glm::vec3{1.0f, 0.0f,1.0f}},

        {glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec3{0.0f, 1.0f,1.0f}},
        {glm::vec3{0.5f, -0.5f, -0.5f},  glm::vec3{1.0f, 1.0f,1.0f}},
        {glm::vec3{0.5f, -0.5f, 0.5f},   glm::vec3{1.0f, 0.0f,1.0f}},
        {glm::vec3{0.5f, -0.5f, 0.5f},   glm::vec3{1.0f, 0.0f,1.0f}},
        {glm::vec3{-0.5f, -0.5f, 0.5f},  glm::vec3{0.0f, 0.0f,1.0f}},
        {glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec3{0.0f, 1.0f,1.0f}},

        {glm::vec3{-0.5f, 0.5f, -0.5f},  glm::vec3{0.0f, 1.0f,1.0f}},
        {glm::vec3{0.5f, 0.5f, -0.5f},   glm::vec3{1.0f, 1.0f,1.0f}},
        {glm::vec3{0.5f, 0.5f, 0.5f},    glm::vec3{1.0f, 0.0f,1.0f}},
        {glm::vec3{0.5f, 0.5f, 0.5f},    glm::vec3{1.0f, 0.0f,1.0f}},
        {glm::vec3{-0.5f, 0.5f, 0.5f},   glm::vec3{0.0f, 0.0f,1.0f}},
        {glm::vec3{-0.5f, 0.5f, -0.5f},  glm::vec3{0.0f, 1.0f,1.0f}}

};


const auto random_colored_cube_data = [] (int32_t n_of_v) -> AdvancedVertex* {
    auto ptr = static_cast<AdvancedVertex*>(calloc(n_of_v, sizeof(AdvancedVertex)));
    for (int32_t i = 0; i < n_of_v; i++) {
        ptr[i].position.x = random_real_between<float>(-1, 1);
        ptr[i].position.y = random_real_between<float>(-1, 1);
        ptr[i].position.z = random_real_between<float>(-1, 1);
        ptr[i].color.r = random_real_between<float>(-1, 1);
        ptr[i].color.g = random_real_between<float>(-1, 1);
        ptr[i].color.b = random_real_between<float>(-1, 1);
    }

    return ptr;
};