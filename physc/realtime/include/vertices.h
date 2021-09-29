#pragma once

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
struct SampleSceneVertex {
    glm::vec3 position;
    glm::vec2 tex_coords;
};

static constexpr SampleSceneVertex vertices[] = {
        {glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 0.0f}},
        {glm::vec3{0.5f, -0.5f, -0.5f},  glm::vec2{1.0f, 0.0f}},

};

// clang-format off
static constexpr SampleSceneVertex textured_cube_vertices[] = {
        {glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 0.0f}},
        {glm::vec3{0.5f, -0.5f, -0.5f}, glm::vec2{1.0f, 0.0f}},
        {glm::vec3{0.5f, 0.5f, -0.5f}, glm::vec2{1.0f, 1.0f}},
        {glm::vec3{0.5f, 0.5f, -0.5f}, glm::vec2{1.0f, 1.0f}},
        {glm::vec3{-0.5f, 0.5f, -0.5f}, glm::vec2{0.0f, 1.0f}},
        {glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 0.0f}},

        {glm::vec3{-0.5f, -0.5f, 0.5f}, glm::vec2{0.0f, 0.0f}},
        {glm::vec3{0.5f, -0.5f, 0.5f}, glm::vec2 {1.0f, 0.0f}},
        {glm::vec3{0.5f, 0.5f, 0.5f}, glm::vec2{1.0f, 1.0f}},
        {glm::vec3{0.5f, 0.5f, 0.5f}, glm::vec2{1.0f, 1.0f}},
        {glm::vec3{-0.5f, 0.5f, 0.5f}, glm::vec2{0.0f, 1.0f}},
        {glm::vec3{-0.5f, -0.5f, 0.5f}, glm::vec2{0.0f, 0.0f}},

        {glm::vec3{-0.5f, 0.5f, 0.5f}, glm::vec2{1.0f, 0.0f}},
        {glm::vec3{-0.5f, 0.5f, -0.5f}, glm::vec2{1.0f, 1.0f}},
        {glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 1.0f}},
        {glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 1.0f}},
        {glm::vec3{-0.5f, -0.5f, 0.5f}, glm::vec2{0.0f, 0.0f}},
        {glm::vec3{-0.5f, 0.5f, 0.5f}, glm::vec2{1.0f, 0.0f}},

        {glm::vec3{0.5f, 0.5f, 0.5f}, glm::vec2{1.0f, 0.0f}},
        {glm::vec3{0.5f, 0.5f, -0.5f}, glm::vec2{1.0f, 1.0f}},
        {glm::vec3{0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 1.0f}},
        {glm::vec3{0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 1.0f}},
        {glm::vec3{0.5f, -0.5f, 0.5f}, glm::vec2{0.0f, 0.0f}},
        {glm::vec3{0.5f, 0.5f, 0.5f}, glm::vec2{1.0f, 0.0f}},

                      {} -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                      {0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
                       {0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                        {0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                         {-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                          {-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

                           {-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
                            {0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                             {0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                              {0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                               {-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
                                {-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};
// clang-format on