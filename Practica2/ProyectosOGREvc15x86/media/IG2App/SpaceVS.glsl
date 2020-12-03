#version 330 core
in vec4 vertex; // atributos de los vértices a procesar
in vec2 uv0; // coordenadas de textura 0
in vec2 uv1; // coordenadas de textura 0
uniform mat4 modelViewProjMat; // constante de programa
uniform float SinTiempo;
out vec2 vUv0; // out del vertex shader
out vec2 vUv1; // out del vertex shader

void main() {
    // se pasan las coordenadas de textura
    //SinTiempo = ((SinTiempo * 0.25) + 0.75);
    float sinAjuste = ((SinTiempo * 0.25) + 0.75);
    vUv0 = ((uv0 - 0.5) * sinAjuste + 0.5); 
    vUv1 = ((uv1 - 0.5) * sinAjuste + 0.5);
    gl_Position = modelViewProjMat * vertex; //obligatorio
    // (Clipping coordinates)
}