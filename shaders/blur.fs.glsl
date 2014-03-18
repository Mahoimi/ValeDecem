#version 330 core

in vec2 v_UV;

uniform sampler2D Texture;
uniform float SampleCount;

out vec4 Color;

void main (){
    vec3 blurredPixel = vec3(0);
    int halfSamples = int(SampleCount) / 2;

    for (int i = -halfSamples; i < halfSamples + 1; i++){
        for ( int j = -halfSamples; j < halfSamples + 1; j++) {
            vec3 sample  = texelFetch(Texture, ivec2(gl_FragCoord)*2 + ivec2(i,j), 0).rgb;
            blurredPixel =  blurredPixel + sample;
        }
    }

    blurredPixel = blurredPixel / (SampleCount*SampleCount);
    Color = vec4(blurredPixel,1);
}
