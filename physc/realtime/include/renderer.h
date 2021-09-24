#pragma once

#include <cstdint>
#include <memory>
#include <functional>

class GLFWwindow;
class Shader;

typedef void (*InputHandler) (GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods);

class Renderer{
public:
    Renderer();

    std::function<void()> drawTexturedRectangle();

    std::function<void()> drawTexturedCube();

    void prepareBufferObjects_(const float *vertices, const int32_t vertices_size,
                               const int32_t *indices = nullptr, const int32_t indices_size = -1) noexcept;

    uint32_t prepareTexture_(uint32_t *wall_texture, uint32_t *face_texture,
                         int32_t vertex_shader_idx, int32_t fragment_shader_idx);

    void destroy() noexcept;
private:

private:
    uint32_t vbo_{0};
    uint32_t ebo_{0};
    uint32_t vao_{0};
};
