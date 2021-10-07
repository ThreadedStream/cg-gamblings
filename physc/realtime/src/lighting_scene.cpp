#include <include/lighting_scene.h>
#include <glad.h>
#include <include/vertices.h>
#include <GLFW/glfw3.h>
#include <include/shader.h>
#include <ext/matrix_clip_space.hpp>
#include <include/filesystem.h>


LightingScene::LightingScene() {
    glGenVertexArrays(1, &vao_);
}

void LightingScene::setup() {
    prepareBufferObjects();

    projection_ = glm::perspective(glm::pi<float>() * .25, 800.0 / 600.0, 0.1, 10000.0);

    model_ = glm::identity<glm::mat4>();
}

void LightingScene::draw() {
    static glm::mat4 mvp;

    Shader::use(shader_program_id_);

    if (dirty_) {
        mvp = projection_ * camera_.view() * model_;
        dirty_ = false;
    }

    Shader::passUniformMat4(mvp, "mvp", shader_program_id_);

    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void LightingScene::prepareBufferObjects() {
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    // NOTE(threadedstream): beget vertex buffer object
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    // TODO(threadedstream): sizeof() might not work in case if "vertices" is not
    // an statically allocated array
    glBufferData(GL_ARRAY_BUFFER, sizeof(colored_cube_vertices), colored_cube_vertices, GL_STATIC_DRAW);

    const int32_t stride = sizeof(Vertex);

    const auto position_offset = offsetof(Vertex, position);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *) position_offset /* 0 */);
    glEnableVertexAttribArray(0);

    // NOTE(threadedstream): binding texture coordinates attribute
    const auto color_offset = offsetof(Vertex, color);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void *) color_offset);
    glEnableVertexAttribArray(1);

    char *vertex_shader_source = fs::loadShaderFromFile("D:/toys/physc/physc/shaders/phong_vs.glsl");
    assert(vertex_shader_source && "failed to load vertex shader");
    char *fragment_shader_source = fs::loadShaderFromFile("D:/toys/physc/physc/shaders/phong_fs.glsl");
    assert(fragment_shader_source && "failed to load fragment shader");

    shader_program_id_ = Shader::linkShaders(vertex_shader_source,
                                             fragment_shader_source);

    // unload shaders
    free(vertex_shader_source);
    free(fragment_shader_source);

    Shader::use(shader_program_id_);
    Shader::passUniformVec4(glm::vec3{0, 10, -2}, "light_source_position", )
    Shader::passUniformVec4(ambient_color_, "ambient_color", shader_program_id_);
    Shader::passUniformVec4(diffuse_color_, "diffuse_color", shader_program_id_);
    Shader::passUniformVec4(specular_color_, "specular_color", shader_program_id_);
}

void LightingScene::handleKeyboardInput(GLFWwindow *window, const float dt) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera_.move(dt, Direction::FORWARD);
        dirty_ = true;
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera_.move(dt, Direction::BACKWARD);
        dirty_ = true;
    } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera_.move(dt, Direction::LEFT);
        dirty_ = true;
    } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera_.move(dt, Direction::RIGHT);
        dirty_ = true;
    } else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, 1);
    }
}


void LightingScene::destroy() {
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
}

void LightingScene::prepareTextureData() {

}

