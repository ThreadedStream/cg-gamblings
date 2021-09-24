#pragma once

#include "shader_sources.h"
#include <cstdint>
#include <ext/matrix_float4x4.hpp>

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

// TODO(threadedstream): probably, organize a structure where there's a ShaderProvider class
// having Shader as a member.
class Shader final {
public:
    Shader() = default;

    static void use(uint32_t shader_program_id) noexcept;

    // NOTE(threadedstream): all transfers of data from cpu to gpu MUST be
    // carried out after calling use()
    static void passUniformMat4(const glm::mat4 &mat, const char * identifier,
                                       uint32_t shader_program_id) noexcept;

    static void passUniformInt(int32_t value, const char * identifier, uint32_t shader_program_id) noexcept;

    static uint32_t linkShaders(const char *vertex_shader_source, const char *fragment_shader_source);

private:
};