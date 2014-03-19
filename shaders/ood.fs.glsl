#version 330 core

in vec3 NormalFromView;
in vec3 PositionFromView;

uniform vec3 MeshColor;

out vec3 Color;

mat3 Rotate(float angle){
    return mat3(vec3(cos(angle), 0, -sin(angle)), vec3(0, 1, 0), vec3(sin(angle), 0, cos(angle)));
}

void main() {
    float theta = clamp(abs(dot(normalize(NormalFromView), normalize(Rotate(0.3)*(-PositionFromView)))), 0, 1);
    Color = MeshColor * theta;
}
