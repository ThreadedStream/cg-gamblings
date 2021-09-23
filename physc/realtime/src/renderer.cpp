#include <include/renderer.h>
#include <spdlog/spdlog.h>
#include <glad.h>
#include <GLFW/glfw3.h>


static void framebufferResizedCallback(GLFWwindow *window, int32_t width, int32_t height) {
    glViewport(0, 0, width, height);
}

bool Renderer::setup_(const int32_t width, const int32_t height,
                      const char *const title) noexcept {
    window_ = glfwCreateWindow(width, height, title, nullptr, nullptr);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!window_) {
        spdlog::error("failed to initialize a window");
        return false;
    }

    glfwMakeContextCurrent(window_);
    glfwSetFramebufferSizeCallback(window_, framebufferResizedCallback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        spdlog::error("failed to load gl procs");
        return false;
    }
}

void Renderer::setInputHandler(InputHandler &&input_handler) const noexcept {
    glfwSetKeyCallback(window_, input_handler);
}

void Renderer::drawTexturedTriangle(const Shader& shader) {

}

void Renderer::prepareBufferObjects_(const float *vertices, const int32_t *indices) noexcept {
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    // NOTE(threadedstream): beget vertex buffer object
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    // TODO(threadedstream): sizeof() might not work in case if "vertices" is not
    // an statically allocated array
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    if (indices) {
        // NOTE(threadedstream): beget element array buffer object
        glGenBuffers(1, &ebo_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }
}



