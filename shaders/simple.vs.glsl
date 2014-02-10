#version 330 core

layout(location = 0)in vec3 position;
layout(location = 1)in vec3 normal_coords;

uniform mat4 MVP;

out vec3 vNormalCoords;

void main(){
    gl_Position = MVP * vec4(position, 1.f);
    vNormalCoords = normal_coords;
}
