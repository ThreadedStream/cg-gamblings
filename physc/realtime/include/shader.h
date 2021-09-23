#include "shader_sources.h"


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


// TODO(threadedstream): hinder implementation, make structure look more "layerized"
// By "layerization" i mean the structure when one has the files containing the actual implementation
// details of some functionality, but also another header file serving as an intermediate level
// between functionality and the rest of the world.
class Shader final{
public:
    explicit Shader(const uint32_t vertex_shader_type, const uint32_t fragment_shader_type):
            shader_program_id_{0} {
        setup_();
    }

    inline void use() const noexcept {
        glUseProgram(shader_program_id_);
    }

    // NOTE(threadedstream): all transfers of data from cpu to gpu MUST be
    // carried out after calling use() function
    inline void passUniformMat4(const glm::mat4& mat, const char* const identifier) const noexcept{
        // TODO(threadedstream): cache uniform locations
        auto mat_location = glGetUniformLocation(shader_program_id_, identifier);
        glUniformMatrix4fv(mat_location, 1, GL_FALSE, glm::value_ptr(mat));
    }

    inline void passUniformInt(const int32_t value, const char* const identifier) const noexcept{
        auto int_location = glGetUniformLocation(shader_program_id_, identifier);
        glUniform1i(int_location, value);
    }

private:
    void setup_() {
        uint32_t vertex_shader{0}, fragment_shader{0};
        int32_t success{0}; char error_buffer[512];

        // creating a vertex shader
        CREATE_SHADER(vertex_shader, textured_vertex_shader, GL_VERTEX_SHADER)
        CHECK_FOR_SHADER_ERRORS(vertex_shader, GL_COMPILE_STATUS)

        // creating a fragment shader
        CREATE_SHADER(fragment_shader, textured_fragment_shader, GL_FRAGMENT_SHADER)
        CHECK_FOR_SHADER_ERRORS(fragment_shader, GL_COMPILE_STATUS)

        shader_program_id_ = glCreateProgram();

        glAttachShader(shader_program_id_, vertex_shader);
        glAttachShader(shader_program_id_, fragment_shader);
        glLinkProgram(shader_program_id_);

        CHECK_FOR_SHADER_ERRORS(shader_program_id_, GL_LINK_STATUS)

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }

private:
    uint32_t shader_program_id_;

};