#include <include/lighting_scene.h>
#include <include/vertices.h>
#include <include/shader.h>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <ext/matrix_clip_space.hpp>


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
    glBufferData(GL_ARRAY_BUFFER, sizeof(textured_cube_vertices), textured_cube_vertices , GL_STATIC_DRAW);

    const int32_t stride = sizeof(SimpleVertex);


    const auto position_offset = offsetof(SimpleVertex, position);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*) position_offset /* 0 */);
    glEnableVertexAttribArray(0);

    // NOTE(threadedstream): binding texture coordinates attribute
    const auto tex_coords_offset = offsetof(SimpleVertex, tex_coords);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*) tex_coords_offset);
    glEnableVertexAttribArray(1);

    shader_program_id_ = Shader::linkShaders(shader_map[COLORED_VERTEX_SHADER_3D], shader_map[COLORED_FRAGMENT_SHADER_3D]);
}

void LightingScene::handleKeyboardInput(GLFWwindow* window, float dt) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera_.move(dt, Direction::FORWARD);
        dirty_ = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera_.move(dt, Direction::BACKWARD);
        dirty_ = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera_.move(dt, Direction::LEFT);
        dirty_ = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera_.move(dt, Direction::RIGHT);
        dirty_ = true;
    }
}


void LightingScene::prepareTextureData() {

}

