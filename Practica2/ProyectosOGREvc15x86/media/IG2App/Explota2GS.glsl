#version 330 core
layout (triangles) in; // procesa un triángulo: recibe 1 triángulo y
layout (triangle_strip, max_vertices = 3) out; // emite 1 triángulo

uniform mat4 modelViewProjMat; // para pasar a Clip-Space

uniform mat4 modelViewMat;
uniform mat4 normalMat; 

uniform float Tiempo2PI; //Para la rotacion
uniform float Tiempo; //Para ir aumentando la escala
const float VD = 50; // longitud del desplazamiento

in vec2[] vUv0;
in vec3[] vVertex;
in vec3[] vNormal;

out vec2 vUvF;
out vec3 vVertexF;
out vec3 vNormalF;

//Calculo del baricentro del triangulo formado por 3 vertices
vec3 barycenter(vec3 vertex[3]) {
    return (vertex[0] + vertex[1] + vertex[2])/3;
}

//Multiplica una posicion por la matriz de rotacion en el eje y
vec3 rotate(vec3 posDes, float angle){
    return posDes * mat3(cos(angle), 0, sin(angle), 0,1,0,-sin(angle),0, cos(angle));
}

vec3 normalVec(vec3 vertex[3]) { 
    return normalize(cross(vertex[1] - vertex[0], vertex[2] - vertex[1]));
} // vector normal al triángulo

void main() {
    vec3 vertices[3] = vec3[]( gl_in[0].gl_Position.xyz * Tiempo, gl_in[1].gl_Position.xyz* Tiempo, gl_in[2].gl_Position.xyz * Tiempo );

    for(int i = 0; i < 3; ++i)
        vertices[i] = rotate(vertices[i], Tiempo2PI);

    vec3 barycenter = barycenter(vertices);
    vec3 dir = normalize(barycenter);
   
    vNormalF = normalize(vec3(normalMat * vec4(normalVec(vertices),0)));

    for (int i=0; i<3; ++i) { // para emitir 3 vértices
        vec3 posDes = vertices[i] + dir * (VD * Tiempo);

        // vértice desplazado (los 3 en la misma dirección)
        gl_Position = modelViewProjMat * vec4(posDes,1.0);

        //Multiplicamos por dos las coordenadas de la textura para que no se vea tan pequeña
        vUvF = vUv0[i] * 2;

        vVertexF = modelViewMat * posDes;
        
        EmitVertex();
    }
    EndPrimitive();
}