#version 330 core
in vec2 vUv0;
uniform sampler2D RTT0; // textura con la escena
uniform float kernel[9];
out vec4 fFragColor;

void main() {

    //Tamaño de la textura
    ivec2 texSize = textureSize(RTT0, 0);
    //Distancia absoluta a la que se encuentra cualquier pixel vecino
    float incS = 1. / float(texSize.s);
    float incT = 1. / float(texSize.t);

    // incrementos para acceder a los 9 pixeles vecinos
    vec2 incUV[9] = vec2[]( 
        vec2(-incS, incT), // top‐left
        vec2(0, incT) , // top‐center
        vec2(incS, incT) , // top‐right
        vec2(-incS, 0) , // center‐left
        vec2(0, 0) , // center‐center
        vec2(incS, 0) , // center‐right
        vec2(-incS, -incT) , // bottom‐left
        vec2(0, -incT) , // bottom‐center
        vec2(incS, -incT) // bottom‐right
    );

    vec4 color = vec4(0.0);
    for(int i = 0; i < 9; i++) {
        //Coordenadas del pixel vecino
        vec2 uvOf = vUv0 + incUV[i];
        //Color del pixel vecino multiplicado por kernel[i] para que la suma total no pase de 1
        vec4 texelD = texture(RTT0, uvOf) * kernel[i];
        //Adicion del color del pixel vecino i al final
        color += texelD;
    }
    fFragColor = color;

}