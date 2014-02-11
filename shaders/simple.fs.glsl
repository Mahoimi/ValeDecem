#version 330 core

in vec2 v_UV;

uniform sampler2D Diffuse;

out vec4 Color;

void main(){
    Color = texture(Diffuse, v_UV);
}
