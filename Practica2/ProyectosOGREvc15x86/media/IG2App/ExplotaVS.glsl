#version 330 core // archivo ExplotaVS.glsl
in vec4 vertex;
in vec3 normal;
in vec2 uv0; // coordenadas de textura 0

out vec2 vUv0; // out del vertex shader
out vec3 vNormal;

void main() {
    vUv0 = uv0;
    gl_Position = vertex; // El GS tiene que transformar las coordenadas de gl_Position al espacio de corte
    vNormal = normalize(normal);
}