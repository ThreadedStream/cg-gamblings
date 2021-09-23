

namespace shaders {
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

    const char *textured_vertex_shader = R"shader(
    #version 330 core
    layout (location = 0) in vec3 vertex_pos;
    layout (location = 1) in vec3 vertex_color;
    layout (location = 2) in vec2 tex_coords;

    out vec3 color;
    out vec2 texture_coords;

    uniform mat4 mvp;

    void main() {
        gl_Position = mvp * vec4(vertex_pos, 1.0);
        color = vertex_color;
        texture_coords = tex_coords;
    }
    )shader";

    const char *textured_fragment_shader = R"shader(
    #version 330 core
    // prefix "out" is relevant only in the context of vertex shader
    in vec3 color;
    in vec2 texture_coords;

    out vec4 frag_color;

    uniform sampler2D texture_sampler;

    void main(){
        // "texturizing" vertices
        frag_color = texture(texture_sampler, texture_coords);
    }
    )shader";

    // TODO(threadedstream): build another residence for vertices
    constexpr float triangle_vertices[] = {
            0.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f
    };

    constexpr float cube_vertices[] = {
            -1.0f, -1.0f, -1.0f, // triangle 1 : begin
            -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, // triangle 1 : end
            1.0f, 1.0f, -1.0f, // triangle 2 : begin
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f, // triangle 2 : end
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f
    };

    constexpr float vertices[] = {
            // positions          // colors                 // texture coords
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, /*red*/     1.0f, 1.0f,   // top right
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, /*green*/  1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,           0.0f, 0.0f,   // bottom left
            -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,            0.0f, 1.0f    // top left
    };

}