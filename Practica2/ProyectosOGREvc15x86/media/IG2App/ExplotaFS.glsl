#version 330 core // archivo ExplotaFS.glsl

in vec2 vUvF; // out del vertex shader
in vec3 vVertexF;
in vec3 vNormalF;

uniform float Flipping;
uniform sampler2D texturaInside; // tipo sampler2D para texturas 2D
uniform sampler2D texturaOutside; // ‐> unidades de textura (int)

uniform vec3 lightAmbient; // intensidades de la luz
uniform vec3 lightDiffuse;
uniform vec4 lightPosition; // datos de la fuente de luz en view space

out vec4 fFragColor;

float diff(vec3 cVertex, vec3 cNormal)
{
    vec3 lightDir = lightPosition.xyz; // directional light ?
    if (lightPosition.w == 1) { 
        lightDir = lightPosition.xyz - cVertex;
    }
    return max(dot(cNormal, normalize(lightDir)), 0.0);
    // dot: coseno ángulo
}


void main() {
    vec3 ambient;
    vec3 materialDiffuse;
    vec3 diffuse;
    vec4 color;

    bool frontFacing = (Flipping > -1) ? gl_FrontFacing : !gl_FrontFacing;

    //Cara exterior de la esfera
    if (frontFacing) { 
        //Calculo de componente difusa
        materialDiffuse = vec3(texture(texturaOutside, vUvF));    
        diffuse = diff(vVertexF, vNormalF) * lightDiffuse * materialDiffuse;
        //Calculo de componente ambiente
        ambient = lightAmbient * materialDiffuse;
        //Definicion del color y mezcla con la textura
        color = vec4((ambient + diffuse), 1.0);
        vec4 colorOutside = vec4(materialDiffuse, 1.0); 
        color = color * colorOutside;
    }
    //Cara interior de la esfera
    else {
        //Calculo de componente difusa
        materialDiffuse = vec3(texture(texturaInside, vUvF));    
        diffuse = diff(vVertexF, -vNormalF) * lightDiffuse * materialDiffuse;
        //Calculo de componente ambiente
        ambient = lightAmbient * materialDiffuse;
        //Definicion del color y mezcla con la textura
        color = vec4((ambient + diffuse), 1.0); // + specular
        vec4 texturaInside = vec4(materialDiffuse, 1.0); 
        color = color * texturaInside;
    }
    fFragColor = color;
}