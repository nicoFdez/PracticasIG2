#version 330 core
in vec2 vUv0; // out del vertex shader
in vec3 vVertex;
in vec3 vNormal;

uniform float Flipping;

uniform sampler2D texturaCorrosion; // tipo sampler2D para texturas 2D
uniform sampler2D texturaBumpy;
uniform vec4 InColor;
uniform vec4 OutColor;

uniform vec3 lightAmbient; // intensidades de la luz
uniform vec3 lightDiffuse;
uniform vec4 lightPosition; // datos de la fuente de luz en view space


uniform vec3 materialDiffuse; // datos del material ¡Front=Back!

out vec4 fFragColor; // out del fragment shader

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
    vec3 colorCorrosion = vec3(texture(texturaCorrosion, vUv0)); // acceso a téxel
    vec4 color;
    if(colorCorrosion.r > 0.6){
        discard;
    }
    else{
        // ambient
        vec3 ambient = lightAmbient * materialDiffuse;

        // diffuse en view space
        vec3 diffuse;
        bool frontFacing = (Flipping > -1)? gl_FrontFacing : !gl_FrontFacing;
        if (frontFacing){
            diffuse = diff(vVertex, vNormal) * lightDiffuse * materialDiffuse;
            color = vec4((ambient + diffuse), 1.0) * OutColor; // + specular

            vec4 colorBumpy = vec4(vec3(texture(texturaBumpy, vUv0)), 1.0); 
            color = color * colorBumpy;
        } 
        else {
            diffuse = diff(vVertex, -vNormal) * lightDiffuse * materialDiffuse;
            color = vec4((ambient + diffuse), 1.0) * InColor; // + specular
        }
    }

    fFragColor = color; //* intLuzAmb // out
}