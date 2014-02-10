#version 330 core

in vec3 vNormalCoords;

out vec3 color;

void main(){
    color = abs(vNormalCoords);
}
