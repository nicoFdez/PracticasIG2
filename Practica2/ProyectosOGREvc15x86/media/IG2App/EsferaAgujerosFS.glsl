#version 330 core
uniform sampler2D texturaCorrosion; // tipo sampler2D para texturas 2D
uniform float intLuzAmb; // luz ambiente blanca
in vec2 vUv0; // out del vertex shader
uniform vec4 InColor;
uniform vec4 OutColor;
out vec4 fFragColor; // out del fragment shader

void main() {
    vec3 colorCorrosion = vec3(texture(texturaCorrosion, vUv0)); // acceso a téxel
    vec4 color;
    if(colorCorrosion.r < 0.5){
        discard;
    }
    else{
        if (gl_FrontFacing) color = OutColor;
        else color = InColor;
    }
    fFragColor = color; //* intLuzAmb // out
    // mix ‐> (1‐BF).colorL + BF.colorM
    
}