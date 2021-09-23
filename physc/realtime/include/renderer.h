#include <cstdint>


class GLFWwindow;
class Shader;

typedef void (*InputHandler) (GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods);

class Renderer{
    explicit Renderer(const int32_t width, const int32_t height,
                      const char* const title) {


        if (!setup_(width, height, title)){ return; }
    }

    inline void setInputHandler(InputHandler&& input_handler) const noexcept;

    void drawTexturedTriangle(const Shader& shader);

private:
    bool setup_(int32_t width, int32_t height, const char* title) noexcept;
    void prepareBufferObjects_(const float *vertices, const int32_t *indices = nullptr) noexcept;

private:
    GLFWwindow* window_;
    uint32_t vbo_{0};
    uint32_t ebo_{0};
    uint32_t vao_{0};
};
