#version 330 core // archivo NormalesGS.glsl
layout (triangles) in; // procesa un triángulo 
layout (line_strip, max_vertices = 6) out; // genera una línea (vector normal) por cada vértice

// genera 3 líneas ‐> 3 primitivas cada una de 2 vértices
in vec3 gNormal[]; // 3 vectores normales provenientes del Vertex Shader
out vec3 vColor; // color para los vértices de la línea. Al declarar vColor out, cada vértice llevará asociado el color que contenga esta variable en el momento de emitirlo
const float SIZE = 50; // para la longitud de la línea
uniform mat4 modelViewProjMat; // pendiente de realizar

// ‐> // variable out vColor ‐> cada vértice se emite con su color
void generateLine(int index) { // normal al vértice index (0, 1, 2)
    vColor = vec3(1.0, 0, 0); 
    gl_Position = modelViewProjMat * gl_in[index].gl_Position;
    EmitVertex(); // 1º vértice de la línea con color y …

    vColor = vec3(1.0, 1.0, 0); 
    gl_Position = modelViewProjMat * (gl_in[index].gl_Position + vec4(gNormal[index], 0) * SIZE); //Desplazada SIZE en dir normal
    EmitVertex(); // 2º vértice de la línea con color y …

    EndPrimitive(); // línea formada por los 2 vértices emitidos
}

void main()
{
    for (int i=0; i<3; ++i)
        generateLine(i);
}