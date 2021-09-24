#include <shared/defs.hpp>

#include <include/renderer.h>
#include <ext/matrix_transform.hpp>
#include <ext/matrix_clip_space.hpp>
#include <gtc/type_ptr.hpp>
#include <stb_image.h>
#include <include/vertices.h>

constexpr glm::vec3 up = glm::vec3{0.0f, 1.0f, 0.0f};

constexpr float angle = glm::pi<float>() * .5;

class GlobalFrameManager;

static GlobalFrameManager *instance_;

class GlobalFrameManager {
public:
    static GlobalFrameManager *getInstance() {
        if (!instance_) {
            instance_ = new GlobalFrameManager();
        }
        return instance_;
    }


    [[nodiscard]] inline const float dt() const noexcept { return dt_; }

private:
    GlobalFrameManager() : dt_{1 / 60.0f} {};

    float dt_;
};


static auto camera_pos = glm::vec3{0.0f, 0.0f, 3.0f};
static auto camera_front = glm::vec3{0.0f, 0.0f, -1.0f};
static auto camera_up = glm::vec3{0.0f, 1.0f, 0.0f};


glm::mat4 mvpMatrix(const glm::mat4 &projection, const glm::mat4 &model) {
    const glm::mat4 view = glm::lookAt(camera_pos, glm::vec3{0.0f, 0.0f, 0.0f}, up);
    return projection * view * model;
}

//void drawTriangle(const glm::mat4 &mvp) {
//    uint32_t vbo{0}, vao{0}, vertex_shader{0}, fragment_shader{0}, shader_program{0};
//    int32_t success{0};
//    char error_buffer[512];
//    glGenBuffers(1, &vbo);
//
//
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void *>(nullptr));
//    glEnableVertexAttribArray(0);
//
//    // creating a vertex shader
//    CREATE_SHADER(vertex_shader, cube_vertex_shader_source, GL_VERTEX_SHADER)
//    CHECK_FOR_SHADER_ERRORS(vertex_shader, GL_COMPILE_STATUS)
//
//    // creating a fragment shader
//    CREATE_SHADER(fragment_shader, cube_fragment_shader_source, GL_FRAGMENT_SHADER)
//    CHECK_FOR_SHADER_ERRORS(fragment_shader, GL_COMPILE_STATUS)
//
//    shader_program = glCreateProgram();
//
//    glAttachShader(shader_program, vertex_shader);
//    glAttachShader(shader_program, fragment_shader);
//    glLinkProgram(shader_program);
//
//    CHECK_FOR_SHADER_ERRORS(shader_program, GL_LINK_STATUS)
//
//    glDeleteShader(vertex_shader);
//    glDeleteShader(fragment_shader);
//
//    glUseProgram(shader_program);
//    glUniformMatrix4fv(mvp_mat_location, 1, GL_FALSE, glm::value_ptr(mvp));
//
//    glDrawArrays(GL_TRIANGLES, 0, 3);
//}
//
//void drawCube(const glm::mat4 &mvp) {
//    uint32_t vbo{0}, vao{0}, vertex_shader{0}, fragment_shader{0}, shader_program{0};
//    int32_t success{0};
//    char error_buffer[512];
//    glGenBuffers(1, &vbo);
//
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
//    glEnableVertexAttribArray(0);
//
//    // creating a vertex shader
//    CREATE_SHADER(vertex_shader, cube_vertex_shader_source, GL_VERTEX_SHADER)
//    CHECK_FOR_SHADER_ERRORS(vertex_shader, GL_COMPILE_STATUS)
//
//    // creating a fragment shader
//    CREATE_SHADER(fragment_shader, cube_fragment_shader_source, GL_FRAGMENT_SHADER)
//    CHECK_FOR_SHADER_ERRORS(fragment_shader, GL_COMPILE_STATUS)
//
//    shader_program = glCreateProgram();
//
//    glAttachShader(shader_program, vertex_shader);
//    glAttachShader(shader_program, fragment_shader);
//    glLinkProgram(shader_program);
//
//    glDeleteShader(vertex_shader);
//    glDeleteShader(fragment_shader);
//
//    auto mvp_mat_location = glGetUniformLocation(shader_program, "mvp");
//
//    glUseProgram(shader_program);
//    glUniformMatrix4fv(mvp_mat_location, 1, GL_FALSE, glm::value_ptr(mvp));
//
//    CHECK_FOR_SHADER_ERRORS(shader_program, GL_LINK_STATUS)
//
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
//}

// TODO(threadedstream): settle this "passing member function pointer" headache
typedef void (Shader::*SHADER_USE_FUNCTION_PTR) ();


void drawTexturedTriangle(const uint32_t wall_texture,
                          const uint32_t face_texture,
                          const uint32_t vao,
                          const Shader& shader) {

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, wall_texture);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, face_texture);

    shader.use();
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void onKeyPressed(GLFWwindow *window, int32_t key, int32_t scancode, int32_t action, int32_t mods) {
    const float camera_speed = 10.0f;
    switch (key) {
        case GLFW_KEY_W:
            camera_pos += camera_speed * camera_front * GlobalFrameManager::getInstance()->dt();
            break;
        case GLFW_KEY_S:
            camera_pos -= camera_speed * camera_front * GlobalFrameManager::getInstance()->dt();
            break;
        case GLFW_KEY_D:
            camera_pos += glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed *
                          GlobalFrameManager::getInstance()->dt();
            break;
        case GLFW_KEY_A:
            camera_pos -= glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed *
                          GlobalFrameManager::getInstance()->dt();
            break;
        default:
            break;
    }
    spdlog::info("camera_pos: ({}, {}, {})", camera_pos.x, camera_pos.y, camera_pos.z);
}


int main(int argc, const char *argv[]) {
    Renderer renderer(WIDTH, HEIGHT, "I don't know math");

    if (!renderer) {
        return -1;
    }


    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2, 0.4, 0.2, 0.5);
        glClear(GL_COLOR_BUFFER_BIT);
        //const auto view = glm::lookAt(camera_pos, camera_pos + camera_front, up);
        //const auto mvp = projection * view * model;
        drawTexturedTriangle(wall_texture, face_texture,  vao, shader);

        //drawTriangle(mvp);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    // NOTE(threadedstream): should be called in main thread
    glfwTerminate();
    return 0;
}


