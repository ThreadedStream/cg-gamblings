#pragma once

static const char *textured_vertex_shader_2d = R"shader(
    #version 330 core
    layout (location = 0) in vec3 vertex_pos;
    layout (location = 1) in vec3 vertex_color;
    layout (location = 2) in vec2 tex_coords;

    out vec3 color;
    out vec2 texture_coords;

    void main() {
        gl_Position = vec4(vertex_pos, 1.0);
        color = vertex_color;
        texture_coords = tex_coords;
    }
)shader";

static const char *textured_fragment_shader_2d = R"shader(
    #version 330 core
    out vec4 frag_color;

    in vec3 color;
    in vec2 texture_coords;

    uniform sampler2D wall_texture_sampler;
    uniform sampler2D face_texture_sampler;

    void main(){
        // "texturizing" vertices
        vec2 altered_texture_coordinates;
        if (cos(texture_coords.x) == 1) {
            altered_texture_coordinates = -texture_coords;
        }else {
            altered_texture_coordinates = vec2(texture_coords.x, -texture_coords.y);
        }
        frag_color = mix(texture(wall_texture_sampler, altered_texture_coordinates), texture(face_texture_sampler, altered_texture_coordinates), 0.4);
    }
)shader";

static const char *textured_vertex_shader_3d = R"shader(
    #version 330 core
    layout (location = 0) in vec3 vertex_pos;
    layout (location = 1) in vec2 tex_coords;

    out vec3 color;
    out vec2 texture_coords;

    uniform mat4 mvp;

    void main() {
        gl_Position = mvp * vec4(vertex_pos, 1.0);
        texture_coords = tex_coords;
    }
)shader";

static const char *textured_fragment_shader_3d = R"shader(
    #version 330 core
    out vec4 frag_color;

    in vec2 texture_coords;

    uniform sampler2D wall_texture_sampler;
    uniform sampler2D face_texture_sampler;

    void main(){
        // "texturizing" vertices
        frag_color = mix(texture(wall_texture_sampler, texture_coords), texture(face_texture_sampler, texture_coords), 0.4);
    }
)shader";

static const char* colored_vertex_shader_3d = R"shader(
    #version 330 core

    layout(location = 0) in vec3 vertex_pos;
    layout(location = 1) in vec3 vertex_color;

    out vec3 color;

    uniform mat4 mvp;

    void main() {
        gl_Position = mvp * vec4(vertex_pos, 1.0f);
        color = vertex_color;
    }
)shader";

static const char* colored_fragment_shader_3d = R"shader(
    #version 330 core

    in vec3 color;

    uniform vec4 ambient_color;
    uniform vec4 diffuse_color;
    uniform vec4 specular_color;

    out vec4 frag_color;

    vec4 calculate_direction_vector(vec4 to_light_source, vec4 normal) {

    }

    void main() {

        frag_color = vec4(color, 1.0f) * light_color;
    }
)shader";


enum shaders {
    TEXTURED_VERTEX_SHADER_2D,
    TEXTURED_FRAGMENT_SHADER_2D,
    TEXTURED_VERTEX_SHADER_3D,
    TEXTURED_FRAGMENT_SHADER_3D,
    COLORED_VERTEX_SHADER_3D,
    COLORED_FRAGMENT_SHADER_3D
};

static const char *shader_map[] = {
        textured_vertex_shader_2d,
        textured_fragment_shader_2d,
        textured_vertex_shader_3d,
        textured_fragment_shader_3d,
        colored_vertex_shader_3d,
        colored_fragment_shader_3d
};
