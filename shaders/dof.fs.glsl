#version 330 core

in vec2 v_UV;

uniform sampler2D Color;
uniform sampler2D Blur;
uniform sampler2D CoC;


out vec4 OutColor;

void main(void)
{
        float CoCValue = texture(CoC, v_UV).r;
        OutColor = vec4(mix(texture(Color, v_UV).rgb, texture(Blur, v_UV).rgb, CoCValue), 1.0);
}
