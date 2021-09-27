#include <include/renderer.h>
#include <spdlog/spdlog.h>
#include <glad.h>
#include <include/vertices.h>
#include <include/shader.h>
#include <stb_image.h>
#include <glm.hpp>
#include <ext/quaternion_trigonometric.inl>
#include <ext/matrix_clip_space.hpp>
#include <ext/matrix_transform.hpp>



Renderer::Renderer() {

    glGenVertexArrays(1, &vao_);
}

std::function<void()> Renderer::drawTexturedRectangle() {
    prepareBufferObjects_(textured_triangle_vertices, sizeof(textured_triangle_vertices),
                                   textured_triangle_indices, sizeof(textured_triangle_indices));

    uint32_t wall_texture, face_texture;
    prepareTexture_(&wall_texture, &face_texture, TEXTURED_VERTEX_SHADER_2D, TEXTURED_FRAGMENT_SHADER_2D);

    return [=] () -> void {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, wall_texture);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, face_texture);

        glBindVertexArray(vao_);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    };
}

std::function<void()> Renderer::drawTexturedCube() {
    prepareBufferObjects_(textured_cube_vertices, sizeof(textured_cube_vertices));

    uint32_t wall_texture, face_texture;
    auto shader_program_id = prepareTexture_(&wall_texture, &face_texture, TEXTURED_VERTEX_SHADER_3D, TEXTURED_FRAGMENT_SHADER_3D);

    const glm::mat4 projection = glm::perspective(glm::pi<float>() * .25, 800.0 / 600.0, 0.1, 10000.0);

    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 model(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3{1.0f, 0.0f, 0.0f});

    const glm::mat4 mvp = projection * view * model;
    Shader::passUniformMat4(mvp, "mvp", shader_program_id);

    return [=] () -> void {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, wall_texture);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, face_texture);

        glBindVertexArray(vao_);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    };
}

void Renderer::prepareBufferObjects_(const float *vertices, const int32_t vertices_size,
                                     const int32_t *indices, const int32_t indices_size) noexcept {
    glBindVertexArray(vao_);

    // NOTE(threadedstream): beget vertex buffer object
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    // TODO(threadedstream): sizeof() might not work in case if "vertices" is not
    // an statically allocated array
    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);

    if (indices && indices_size) {
        // NOTE(threadedstream): beget element array buffer object
        glGenBuffers(1, &ebo_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);
    }

    const int32_t stride = 5 * sizeof(float);

    // NOTE(threadedstream): binding vertex position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, nullptr /* 0 */);
    glEnableVertexAttribArray(0);

    // NOTE(threadedstream): binding vertex color attribute
//    const auto vertex_color_offset = (void *) (3 * sizeof(float));
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, vertex_color_offset);
//    glEnableVertexAttribArray(1);

    // NOTE(threadedstream): binding texture coordinates attribute
    const auto tex_coords_offset = (void *) (3 * sizeof(float));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, tex_coords_offset);
    glEnableVertexAttribArray(1);
}

uint32_t Renderer::prepareTexture_(uint32_t *wall_texture, uint32_t *face_texture,
                               const int32_t vertex_shader_idx, const  int32_t fragment_shader_idx) {
    // NOTE(threadedstream): setting up the first texture
    glGenTextures(1, wall_texture);
    glBindTexture(GL_TEXTURE_2D, *wall_texture);

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
    glGenTextures(1, face_texture);
    glBindTexture(GL_TEXTURE_2D, *face_texture);

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
    auto shader_program_id = Shader::linkShaders(shader_map[vertex_shader_idx], shader_map[fragment_shader_idx]);

    Shader::use(shader_program_id);
    Shader::passUniformInt(1, "face_texture_sampler", shader_program_id);
    Shader::passUniformInt(0, "wall_texture_sampler", shader_program_id);

    return shader_program_id;
}


void Renderer::destroy() noexcept {
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
    glDeleteBuffers(1, &ebo_);
}