#include <shared/defs.hpp>
#include <SDL.h>
#include <GLES2/gl2.h>
#include <GLFW/glfw3.h>

constexpr float triangle_vertices[] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f
};

#define CHECK_FOR_SHADER_ERRORS(shader, status_type) \
    glGetShaderiv(shader, status_type, &success); \
    if (!success) { \
        glGetShaderInfoLog(shader, sizeof(error_buffer), nullptr, error_buffer); \
        spdlog::error(error_buffer); \
    }

#define CREATE_SHADER(shader, shader_source, shader_type) \
    shader = glCreateShader(shader_type); \
    glShaderSource(shader, 1, &(shader_source), nullptr); \
    glCompileShader(shader); \

const char *vertex_shader_source = R"shader(
    #version 330 core
    layout (location = 0) in vec3 triangle_pos;
    void main() {
        gl_Position = vec4(triangle_pos.x, triangle_pos.y, triangle_pos.z, 1.0f);
    }
)shader";

const char *fragment_shader_source = R"shader(
    #version 330 core
    out vec4 frag_color;

    void main() {
        frag_color = vec4(1.0f, 1.0f, 0.0f, 1.0f);
    }
)shader";

void drawTriangle() {
    uint32_t vbo{0}, vao{0}, vertex_shader{0}, fragment_shader{0}, shader_program{0};
    int32_t success{0};
    char error_buffer[512];
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);

    // creating a vertex shader
    CREATE_SHADER(vertex_shader, vertex_shader_source, GL_VERTEX_SHADER)
    CHECK_FOR_SHADER_ERRORS(vertex_shader, GL_COMPILE_STATUS)

    // creating a fragment shader
    CREATE_SHADER(fragment_shader, fragment_shader_source, GL_FRAGMENT_SHADER)
    CHECK_FOR_SHADER_ERRORS(fragment_shader, GL_COMPILE_STATUS)

    shader_program = glCreateProgram();

    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    CHECK_FOR_SHADER_ERRORS(shader_program, GL_LINK_STATUS)

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glUseProgram(shader_program);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}


int main(int argc, const char *argv[]) {
    GLFWwindow *window;
    if (!glfwInit())
        return -1;

    spdlog::info("init has been successful");

    window = glfwCreateWindow(WIDTH, HEIGHT, "i don't know math", nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    spdlog::info("window has been initialized");

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        drawTriangle();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // NOTE(threadedstream): should be called in main thread
    glfwTerminate();
    return 0;
}

