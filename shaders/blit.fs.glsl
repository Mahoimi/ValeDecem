#version 330 core

in vec2 v_UV;

uniform sampler2D Texture;

out vec4 Color;

void main(void)
{
	vec3 color = texture(Texture, v_UV).rgb;
	Color = vec4(color, 1.0);
}
