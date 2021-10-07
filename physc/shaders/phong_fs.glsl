#version 330 core

in vec3 color;
in vec3 normal;
in vec3 light_source_position;
in vec3 to_viewer_direction;

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

    frag_color = ambient_color + diffuse_color + specular_color;
}
