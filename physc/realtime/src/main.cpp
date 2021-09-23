#include <shared/defs.hpp>

#include <ext/matrix_transform.hpp>
#include <ext/matrix_clip_space.hpp>
#include <gtc/type_ptr.hpp>
#include <include/shader.h>
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
    uint32_t vbo{0}, ebo{0}, vao{0};

    GLFWwindow *window;
    if (!glfwInit())
        return -1;

    spdlog::info("init has been successful");

    window = glfwCreateWindow(WIDTH, HEIGHT, "i don't know math", nullptr, nullptr);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const glm::mat4 projection = glm::perspective(angle, static_cast<float>(WIDTH) / static_cast<float>(HEIGHT),
                                                  0.1f, 10000.0f);

    const glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3{10.0f});

    if (!window) {
        glfwTerminate();
        return -1;
    }


    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        spdlog::error("failed to initialize glad");
        glfwTerminate();
        return -1;
    }

    spdlog::info("window has been initialized");

    // NOTE(threadedstream): beget vertex array object


    // NOTE(threadedstream): 8 refers to a number of parameters
    // i.e 3 position components, 3 color components, 2 texture components
    // all of a float type, hence multiplied by sizeof(float).
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

    Shader shader(TEXTURED_VERTEX_SHADER, TEXTURED_FRAGMENT_SHADER);

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
    shader.passUniformInt(0, "wall_texture_sampler");
    shader.passUniformInt(1, "face_texture_sampler");

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


