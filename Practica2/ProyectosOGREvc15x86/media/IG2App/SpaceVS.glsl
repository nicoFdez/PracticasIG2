#version 330 core
in vec4 vertex; // atributos de los vértices a procesar
in vec2 uv0; // coordenadas de textura 0
uniform mat4 modelViewProjMat; // constante de programa
uniform float SinTiempo;
out vec2 vUv0; // out del vertex shader
out vec2 vUv1; // out del vertex shader

void main() {
    //Calculo de ajuste del seno para que no se salgan las coordenadas de textura
    float sinAjuste = ((SinTiempo * 0.25) + 0.75);
    vUv0 = uv0;
    //Calculo de coordenadas del space con el "zoom"
    vUv1 = ((uv0 - 0.5) * sinAjuste + 0.5);
    gl_Position = modelViewProjMat * vertex; //obligatorio
}