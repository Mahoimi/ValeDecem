#version 330 core

in vec2 uv;

uniform sampler2D Texture;

out vec4 Color;

void main(void)
{
	vec3 color = texture(Texture, uv).rgb;
	Color = vec4(color, 1.0);
}
