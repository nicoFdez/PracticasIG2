#version 330 core // archivo ExplotaFS.glsl

in vec2 vUvF; // out del vertex shader

uniform float Flipping;
uniform sampler2D texturaInside; // tipo sampler2D para texturas 2D
uniform sampler2D texturaOutside; // ‐> unidades de textura (int)

out vec4 fFragColor;

void main() {
    bool frontFacing = (Flipping > -1)? gl_FrontFacing : !gl_FrontFacing;
    if (frontFacing) {
        fFragColor = vec4(vec3(texture(texturaOutside, vUvF)), 1.0); // out
    }
    else {
        fFragColor = vec4(vec3(texture(texturaInside, vUvF)), 1.0); // out
    }
}