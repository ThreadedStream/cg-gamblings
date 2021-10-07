#include <include/shader.h>
#include <spdlog/spdlog.h>
#include <glad.h>
#include <gtc/type_ptr.hpp>

uint32_t Shader::linkShaders(const char *vertex_shader_source, const char *fragment_shader_source) {
    uint32_t vertex_shader{0}, fragment_shader{0}, shader_program_id{0};
    int32_t success{0};
    char error_buffer[512];

    // creating a vertex shader
    CREATE_SHADER(vertex_shader, vertex_shader_source, GL_VERTEX_SHADER)
    CHECK_FOR_SHADER_ERRORS(vertex_shader, GL_COMPILE_STATUS)

    // creating a fragment shader
    CREATE_SHADER(fragment_shader, fragment_shader_source, GL_FRAGMENT_SHADER)
    CHECK_FOR_SHADER_ERRORS(fragment_shader, GL_COMPILE_STATUS)

    shader_program_id = glCreateProgram();

    glAttachShader(shader_program_id, vertex_shader);
    glAttachShader(shader_program_id, fragment_shader);
    glLinkProgram(shader_program_id);

    CHECK_FOR_SHADER_ERRORS(shader_program_id, GL_LINK_STATUS)

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader_program_id;
}

void Shader::use(const uint32_t shader_program_id) noexcept {
    glUseProgram(shader_program_id);
}

void Shader::passUniformMat4(const glm::mat4 &mat, const char *const identifier,
                             const uint32_t shader_program_id) noexcept {

// TODO(threadedstream): enable caching of uniforms' location
    auto target_location = glGetUniformLocation(shader_program_id, identifier);
    glUniformMatrix4fv(target_location, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::passUniformInt(const int32_t value, const char *const identifier,
                            const uint32_t shader_program_id) noexcept {

    auto target_location = glGetUniformLocation(shader_program_id, identifier);
    glUniform1i(target_location, value);
}


void Shader::passUniformVec4(const glm::vec4& value, const char* const identifier,
                             const uint32_t shader_program_id) noexcept {

    auto target_location = glGetUniformLocation(shader_program_id, identifier);
    glUniform4fv(target_location, 1, glm::value_ptr(value));
}

