#version 330 core

in vec3 v_Normal;
in vec2 v_UV;

uniform sampler2D Material;
uniform float Specular;

out vec4 Color;
out vec4 Normal;

void main(void)
{
        Color = texture(Material, v_UV);
        Normal = vec4(v_Normal, Specular);
}
