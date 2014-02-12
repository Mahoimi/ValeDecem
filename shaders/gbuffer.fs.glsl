#version 330 core

in vec3 v_Normal;
in vec2 v_UV;

uniform sampler2D Diffuse;
uniform sampler2D Specular;

out vec4 Color;
out vec4 Normal;

void main(void)
{
	float spec = texture(Specular, v_UV).r;
	
	Color = texture(Diffuse, v_UV);
	Normal = vec4(v_Normal, spec);
}