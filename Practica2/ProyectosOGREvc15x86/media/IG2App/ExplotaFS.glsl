#version 330 core // archivo ExplotaFS.glsl

in vec2 vUvF; // out del vertex shader

uniform float Flipping;
uniform sampler2D texturaInside; // tipo sampler2D para texturas 2D
uniform sampler2D texturaOutside; // ‐> unidades de textura (int)

out vec4 fFragColor;

void main() {
    bool frontFacing = (Flipping > -1)? gl_FrontFacing : !gl_FrontFacing;

    //vec3 ambient = lightAmbient * materialDiffuse;
    //vec3 diffuse;
    vec4 color;

    if (frontFacing) {      
        //diffuse = vec3(texture(texturaOutside, vUvF));
        //color = vec4((ambient + diffuse), 1.0); // + specular
        vec4 colorOutside = vec4(vec3(texture(texturaOutside, vUvF)), 1.0); 
        color = /*color **/ colorOutside;
    }
    else {
        //diffuse = vec3(texture(texturaOutside, vUvF));
        //color = vec4((ambient + diffuse), 1.0); // + specular
        vec4 colorInside = vec4(vec3(texture(texturaInside, vUvF)), 1.0); 
        color = /*color **/ colorInside;
    }
    fFragColor = color;
}