#version 330 core

in vec3 color;
in vec3 normal;
in vec3 light_src_pos_vs_out;
in vec3 to_viewer_dir_vs_out;

uniform vec4 ambient_color;
uniform vec4 diffuse_color;
uniform vec4 specular_color;

out vec4 frag_color;

// specular reflection constant
float k_s = 0.2;
// diffuse reflection constant (Lambertian reflectance)
float k_d = 0.5;
// ambient reflection constant
float k_a = 0.1;
// "shininess" constant
float alpha = 0.02;

vec4 calculate_direction_vector(vec4 to_light_source, vec4 normal) {
    vec4 l_hat = normalize(to_light_source);
    vec4 n_hat = normalize(normal);
    return 2 * dot(l_hat, n_hat) * n_hat - l_hat;
}

void main() {
    vec4 ambient_component = k_a * ambient_color;
    vec4 diffuse_component = k_d*(dot(light_src_pos_vs_out, normal)*diffuse_color);
    vec4 R = calculate_direction_vector(vec4(light_src_pos_vs_out, normal);
    vec4 specular_component = k_s * (pow(dot(R, vec4(to_viewer_dir_vs_out, 1.0f)), alpha)) * specular_color;
    frag_color = ambient_component + diffuse_component + specular_component;
}
