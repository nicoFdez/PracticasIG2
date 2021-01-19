#version 330 core // archivo ExplotaGS.glsl
layout (triangles) in; // procesa un triángulo: recibe 1 triángulo y
layout (triangle_strip, max_vertices = 3) out; // emite 1 triángulo

uniform mat4 modelViewProjMat; // para pasar a Clip-Space
uniform float Tiempo; //Para ir incrementando la escala
const float VD = 50; // longitud del desplazamiento

in vec2[] vUv0;
in vec3[] vVertex;
in vec3[] vNormal;

out vec2 vUvF;
out vec3 vVertexF;
out vec3 vNormalF;

vec3 normalVec(vec3 vertex[3]) { 
    return normalize(cross(vertex[1] - vertex[0], vertex[2] - vertex[1]));
} // vector normal al triángulo

void main() {
    vec3 vertices[3] = vec3[]( gl_in[0].gl_Position.xyz, gl_in[1].gl_Position.xyz, gl_in[2].gl_Position.xyz );
    vec3 dir = normalVec(vertices); // -> vec3 dir = normalVec(vertices) para los 3 vértices

    for (int i=0; i<3; ++i) { // para emitir 3 vértices
        // Desplazamiento de cada verice en la direccion de la normal
        vec3 posDes = vertices[i] + dir * (VD * Tiempo);
        // vértice desplazado (los 3 en la misma dirección) 
        //posicion final pasada al clip-space
        gl_Position = modelViewProjMat * vec4(posDes,1.0);
    
        //Multiplicamos por dos para que no se vea tan pequeña la textura
        vUvF = vUv0[i] * 2;

        //Definicion final y emision del vertice
        vVertexF = vVertex[i];
        vNormalF = vNormal[i];
        EmitVertex();
    }
    EndPrimitive();
}