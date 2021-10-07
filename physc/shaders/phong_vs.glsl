#version 330 core

layout(location = 0) in vec3 vertex_pos;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) inout vec3 vertex_normal;

out vec3 color;

uniform mat4 mvp;
uniform vec3 light_source_position;
uniform vec3 to_viewer_direction;

void main() {
   gl_Position = mvp * vec4(vertex_pos, 1.0f);
   color = vertex_color;
}
