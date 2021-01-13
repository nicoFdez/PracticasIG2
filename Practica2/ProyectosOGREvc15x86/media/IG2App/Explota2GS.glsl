#version 330 core // archivo ExplotaGS.glsl
layout (triangles) in; // procesa un triángulo: recibe 1 triángulo y
layout (triangle_strip, max_vertices = 3) out; // emite 1 triángulo

// al no declarar ninguna variable in, estamos suponiendo que el VS no tiene out,
// los vértices no traen asociados atributos, solo las coordenadas

uniform mat4 modelViewProjMat; // para pasar a Clip-Space
uniform float Tiempo2PI;
uniform float Tiempo;
const float VD = 50; // longitud del desplazamiento

in vec2[] vUv0;
in vec3[] vVertex;
in vec3[] vNormal;

out vec2 vUvF;
out vec3 vVertexF;
out vec3 vNormalF;

vec3 barycenter(vec3 vertex[3]) {
    return (vertex[0] + vertex[1] + vertex[2])/3;
}

vec3 rotate(vec3 posDes, float angle){
    return posDes * mat3(cos(angle), 0, sin(angle), 0,1,0,-sin(angle),0, cos(angle));
}

void main() {
    vec3 vertices[3] = vec3[]( gl_in[0].gl_Position.xyz, gl_in[1].gl_Position.xyz, gl_in[2].gl_Position.xyz );
    vec3 barycenter = barycenter(vertices);
    vec3 dir = normalize(barycenter); // para los 3 vértices

    for (int i=0; i<3; ++i) { // para emitir 3 vértices
        vec3 posDes = vertices[i] + dir * (VD * Tiempo);
        
        vec3 dirScale = (vertices[i] - barycenter);
        posDes += dirScale * Tiempo / 4;
        
        posDes = rotate(posDes, Tiempo2PI);
        // vértice desplazado (los 3 en la misma dirección)
        gl_Position = modelViewProjMat * vec4(posDes,1.0);

        vUvF = vUv0[i] * 2;
        vVertexF = vVertex[i];
        vNormalF = rotate(vNormal[i], Tiempo2PI);

        EmitVertex(); // al no declarar ninguna variable out, los vertices del
        // triángulo emitido no llevan asociados atributos, solo las coordenadas
    }
    EndPrimitive();
}