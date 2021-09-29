#include <include/sample_scene.h>
#include <spdlog/spdlog.h>
#include <glad.h>
#include <include/vertices.h>
#include <include/shader.h>
#include <stb_image.h>
#include <GLFW/glfw3.h>
#include <ext/quaternion_trigonometric.inl>
#include <ext/matrix_clip_space.hpp>
#include <ext/matrix_transform.hpp>
#include <include/camera.h>


SampleScene::SampleScene() {
    glGenVertexArrays(1, &vao_);
}

void SampleScene::setup() {
    prepareBufferObjects();
    prepareTextureData();

    // TODO(threadedstream): alter only rotation matrix
    projection_ = glm::perspective(glm::pi<float>() * .25, 800.0 / 600.0, 0.1, 10000.0);

    model_ = glm::rotate(model_, static_cast<float>(glfwGetTime() * 5.0f), glm::vec3{1.0f, 0.0f, 1.0f});
}

// TODO(threadedstream): add delta time parameter
void SampleScene::draw() {
    static glm::mat4 mvp;
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, wall_texture_);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, face_texture_);

    Shader::use(shader_program_id_);

    if (dirty_) {
        mvp = projection_ * camera.view() * model_;
        dirty_ = false;
    }

    Shader::passUniformMat4(mvp, "mvp", shader_program_id_);

    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void SampleScene::destroy() {
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
}

void SampleScene::prepareBufferObjects() {
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    // NOTE(threadedstream): beget vertex buffer object
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    // TODO(threadedstream): sizeof() might not work in case if "vertices" is not
    // an statically allocated array
    glBufferData(GL_ARRAY_BUFFER, sizeof(textured_cube_vertices), textured_cube_vertices, GL_STATIC_DRAW);

    const int32_t stride = 5 * sizeof(float);

    // NOTE(threadedstream): binding vertex position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *) 0 /* 0 */);
    glEnableVertexAttribArray(0);

    // NOTE(threadedstream): binding texture coordinates attribute
    const auto tex_coords_offset = (void *) (3 * sizeof(float));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, tex_coords_offset);
    glEnableVertexAttribArray(1);
}

void SampleScene::prepareTextureData() {
    // NOTE(threadedstream): setting up the first texture
    glGenTextures(1, &wall_texture_);
    glBindTexture(GL_TEXTURE_2D, wall_texture_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
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
    glGenTextures(1, &face_texture_);
    glBindTexture(GL_TEXTURE_2D, face_texture_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    data = stbi_load("../../assets/awesomeface.png", &width, &height, &channels_num, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        spdlog::error("failed to load a face texture");
    }

    stbi_image_free(data);
    shader_program_id_ = Shader::linkShaders(shader_map[TEXTURED_VERTEX_SHADER_3D],
                                             shader_map[TEXTURED_FRAGMENT_SHADER_3D]);

    Shader::use(shader_program_id_);
    Shader::passUniformInt(0, "wall_texture_sampler", shader_program_id_);
    Shader::passUniformInt(1, "face_texture_sampler", shader_program_id_);
}

void SampleScene::handleKeyboardInput(GLFWwindow* window, float dt) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.move(camera_speed_ * dt, Direction::FORWARD);
        dirty_ = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.move(camera_speed_ * dt, Direction::BACKWARD);
        dirty_ = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.move(camera_speed_ * dt, Direction::LEFT);
        dirty_ = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.move(camera_speed_ * dt, Direction::RIGHT);
        dirty_ = true;
    }
}

void SampleScene::handleMouseInput(GLFWwindow* window, float dt) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) {
        double mouse_pos_x, mouse_pos_y;
        glfwGetCursorPos(window, &mouse_pos_x, &mouse_pos_y);
        camera.rotate(mouse_pos_x, mouse_pos_y,dt, first_mouse_);
        last_mouse_pos_x_ = mouse_pos_x;
        last_mouse_pos_y_ = mouse_pos_y;
        dirty_ = true;
    }
}

