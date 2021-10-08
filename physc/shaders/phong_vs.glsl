#version 330 core

layout(location = 0) in vec3 vertex_pos;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) in vec3 vertex_normal;

out vec3 normal;
out vec3 light_src_pos_vs_out;
out vec3 to_viewer_dir_vs_out;


uniform mat4 mvp;
uniform vec3 light_source_position;
uniform vec3 to_viewer_direction;

void main() {
   gl_Position = mvp * vec4(vertex_pos, 1.0f);
   normal = vertex_normal;
   light_src_pos_vs_out = light_source_position;
   to_viewer_dir_vs_out = to_viewer_direction;
}
