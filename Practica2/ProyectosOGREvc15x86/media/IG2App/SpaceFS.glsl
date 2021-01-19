#version 330 core
uniform sampler2D texturaL; // tipo sampler2D para texturas 2D
uniform sampler2D texturaM; // ‐> unidades de textura (int)
in vec2 vUv0; // out del vertex shader
in vec2 vUv1; // out del vertex shader
out vec4 fFragColor; // out del fragment shader

void main() {
    vec3 colorL = vec3(texture(texturaL, vUv0)); // acceso a téxel
    vec3 colorM = vec3(texture(texturaM, vUv1)); // acceso a téxel
    //Multiplicacion de texturas
    vec3 color = colorL * colorM;
    fFragColor = vec4(color, 1.0); // out
}