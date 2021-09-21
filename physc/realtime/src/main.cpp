#include <shared/defs.hpp>
#include <SDL.h>
#include <GLES2/gl2.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <ext/matrix_transform.hpp>
#include <ext/matrix_clip_space.hpp>
#include <gtc/type_ptr.hpp>

constexpr glm::vec3 up = glm::vec3{0.0f, 1.0f, 0.0f};

constexpr float angle = glm::pi<float>() * .5;


constexpr float triangle_vertices[] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f
};

constexpr float cube_vertices[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
};

class GlobalFrameManager;
static GlobalFrameManager * instance_;

class GlobalFrameManager {
public:
    static GlobalFrameManager* getInstance(){
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

const char *triangle_vertex_shader_source = R"shader(
    #version 330 core
    layout (location = 0) in vec3 triangle_pos;
    void main() {
        gl_Position = vec4(triangle_pos.x, triangle_pos.y, triangle_pos.z, 1.0f);
    }
)shader";

const char *triangle_fragment_shader_source = R"shader(
    #version 330 core
    out vec4 frag_color;

    void main() {
        frag_color = vec4(1.0f, 1.0f, 0.0f, 1.0f);
    }
)shader";

const char *cube_vertex_shader_source = R"shader(
    #version 330 core
    layout (location = 0) in vec3 vertex_pos_model;
    uniform mat4x4 mvp;

    void main() {
        gl_Position = mvp * vec4(vertex_pos_model, 1.0f);
    }
)shader";

const char *cube_fragment_shader_source = R"shader(
    #version 330 core
    out vec4 frag_color;

    void main() {
        frag_color = vec4(1.0f, 0.0f, 1.0f, 1.0f);
    }
)shader";

static auto camera_pos = glm::vec3{0.0f, 0.0f, 3.0f};
static auto camera_front = glm::vec3{0.0f, 0.0f, -1.0f};
static auto camera_up = glm::vec3{0.0f, 1.0f, 0.0f};


glm::mat4 mvpMatrix(const glm::mat4& projection, const glm::mat4& model) {
    const glm::mat4 view = glm::lookAt(camera_pos, glm::vec3{0.0f, 0.0f, 0.0f}, up);
    return projection * view * model;
}

void drawTriangle(const glm::mat4& mvp) {
    uint32_t vbo{0}, vao{0}, vertex_shader{0}, fragment_shader{0}, shader_program{0};
    int32_t success{0};
    char error_buffer[512];
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);

    // creating a vertex shader
    CREATE_SHADER(vertex_shader, cube_vertex_shader_source, GL_VERTEX_SHADER)
    CHECK_FOR_SHADER_ERRORS(vertex_shader, GL_COMPILE_STATUS)

    // creating a fragment shader
    CREATE_SHADER(fragment_shader, cube_fragment_shader_source, GL_FRAGMENT_SHADER)
    CHECK_FOR_SHADER_ERRORS(fragment_shader, GL_COMPILE_STATUS)

    shader_program = glCreateProgram();

    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    CHECK_FOR_SHADER_ERRORS(shader_program, GL_LINK_STATUS)

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    auto mvp_mat_location = glGetUniformLocation(shader_program, "mvp");

    glUseProgram(shader_program);
    glUniformMatrix4fv(mvp_mat_location, 1, GL_FALSE, glm::value_ptr(mvp));

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void drawCube(const glm::mat4& mvp) {
    uint32_t vbo{0}, vao{0}, vertex_shader{0}, fragment_shader{0}, shader_program{0};
    int32_t success{0};
    char error_buffer[512];
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // creating a vertex shader
    CREATE_SHADER(vertex_shader, cube_vertex_shader_source, GL_VERTEX_SHADER)
    CHECK_FOR_SHADER_ERRORS(vertex_shader, GL_COMPILE_STATUS)

    // creating a fragment shader
    CREATE_SHADER(fragment_shader, cube_fragment_shader_source, GL_FRAGMENT_SHADER)
    CHECK_FOR_SHADER_ERRORS(fragment_shader, GL_COMPILE_STATUS)

    shader_program = glCreateProgram();

    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    auto mvp_mat_location = glGetUniformLocation(shader_program, "mvp");

    glUseProgram(shader_program);
    glUniformMatrix4fv(mvp_mat_location, 1, GL_FALSE, glm::value_ptr(mvp));

//    const glm::mat4x4 camera_matrix = glm::lookAt(glm::vec3{0.0f, 0.0f, -2.0f},
//                                                  glm::vec3{0.0f, 0.0f, 0.0f},
//                                                  glm::vec3{0.0f, 1.0f, 0.0f});

    CHECK_FOR_SHADER_ERRORS(shader_program, GL_LINK_STATUS)

    glDrawArrays(GL_TRIANGLES, 0, 3 * 12);
}

void onKeyPressed(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods){
    const float camera_speed = 10.0f;
    switch(key) {
        case GLFW_KEY_W:
            camera_pos += camera_speed * camera_front * GlobalFrameManager::getInstance()->dt();
            break;
        case GLFW_KEY_S:
            camera_pos -= camera_speed * camera_front * GlobalFrameManager::getInstance()->dt();
            break;
        case GLFW_KEY_D:
            camera_pos += glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed * GlobalFrameManager::getInstance()->dt();
            break;
        case GLFW_KEY_A:
            camera_pos -= glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed * GlobalFrameManager::getInstance()->dt();
            break;
        default:
            break;
    }
    spdlog::info("camera_pos: ({}, {}, {})", camera_pos.x, camera_pos.y, camera_pos.z);
}


int main(int argc, const char *argv[]) {
    GLFWwindow *window;
    if (!glfwInit())
        return -1;

    spdlog::info("init has been successful");

    window = glfwCreateWindow(WIDTH, HEIGHT, "i don't know math", nullptr, nullptr);

    const glm::mat4 projection = glm::perspective(angle, static_cast<float>(WIDTH) / static_cast<float>(HEIGHT),
                                                  0.1f, 10000.0f);

    const glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3{10.0f});

    if (!window) {
        glfwTerminate();
        return -1;
    }

    spdlog::info("window has been initialized");

    const float radius = 10.0f;
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, onKeyPressed);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        const auto view = glm::lookAt(camera_pos, camera_pos + camera_front, up);
        const auto mvp = projection * view * model;
        drawCube(mvp);
        drawTriangle(mvp);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // NOTE(threadedstream): should be called in main thread
    glfwTerminate();
    return 0;
}


