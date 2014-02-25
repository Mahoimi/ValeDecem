#version 330 core

in vec3 v_UV;

uniform samplerCube SkyboxTexture;

out vec4 Color;

void main()
{
    Color = texture(SkyboxTexture, v_UV);
}
