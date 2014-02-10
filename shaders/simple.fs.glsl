#version 330 core

in vec2 v_UV;

uniform sampler2D Diffuse;

out vec4 color;

void main(){
    color = texture(Diffuse, v_UV);
}
