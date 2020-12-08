#version 330 core
in vec4 vertex; // atributos de los vértices a procesar
in vec3 normal;
in vec2 uv0; // coordenadas de textura 0
in vec2 uv1;

uniform mat4 modelViewMat;
uniform mat4 modelViewProjMat; // constante de programa
uniform mat4 normalMat; 

out vec2 vUv0; // out del vertex shader
out vec2 vUv1;
out vec4 vVertex;
out vec3 vNormal;

void main() {
    // se pasan las coordenadas de textura
    vUv0 = uv0;
    vUv1 = uv1;
    gl_Position = modelViewProjMat * vertex; //obligatorio
    // (Clipping coordinates)
    vVertex = modelViewMat * vertex;
    vNormal = normalize(vec3(normalMat * vec4(normal,0)));
}