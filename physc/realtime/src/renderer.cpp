#include <include/renderer.h>
#include <spdlog/spdlog.h>
#include <glad.h>
#include <include/shader.h>
#include <GLFW/glfw3.h>
#include <include/vertices.h>
#include <stb_image.h>

Renderer::Renderer(const int32_t width, const int32_t height,
                   const char* const title){

    if (!setup_(width, height, title)){ return; }

    // NOTE(threadedstream): do i need to generate vao here?
    glGenVertexArrays(1, &vao_);
}

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

    return true;
}

void Renderer::setInputHandler(InputHandler &&input_handler) const noexcept {
    glfwSetKeyCallback(window_, input_handler);
}

void Renderer::drawTexturedTriangle(const Shader& shader,
                                    const uint32_t wall_texture,
                                    const uint32_t face_texture) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, wall_texture);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, face_texture);

    shader.use();
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
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

    const int32_t stride = 8 * sizeof(float);

    // NOTE(threadedstream): binding vertex position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, nullptr);
    glEnableVertexAttribArray(0);

    // NOTE(threadedstream): binding vertex color attribute
    const auto vertex_color_offset = (void *) (3 * sizeof(float));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, vertex_color_offset);
    glEnableVertexAttribArray(1);

    // NOTE(threadedstream): binding texture coordinates attribute
    const auto tex_coords_offset = (void *) (6 * sizeof(float));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, tex_coords_offset);
    glEnableVertexAttribArray(2);

}

void Renderer::prepareTexture_(const Shader& shader) {
    // NOTE(threadedstream): setting up the first texture
    uint32_t wall_texture;
    glGenTextures(1, &wall_texture);
    glBindTexture(GL_TEXTURE_2D, wall_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    int32_t width, height, channels_num;
    uint8_t *data = stbi_load("../../assets/wall.jpg", &width, &height, &channels_num, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        spdlog::error("failed to load a wall texture");
    }
    stbi_image_free(data);

    // NOTE(threadedstream): setting up the second texture
    uint32_t face_texture;
    glGenTextures(1, &face_texture);
    glBindTexture(GL_TEXTURE_2D, face_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    data = stbi_load("../../assets/awesomeface.png", &width, &height, &channels_num, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else {
        spdlog::error("failed to load a face texture");
    }

    stbi_image_free(data);

    shader.use();
    shader.passUniformInt(1, "face_texture_sampler");
    shader.passUniformInt(0, "wall_texture_sampler");
}
