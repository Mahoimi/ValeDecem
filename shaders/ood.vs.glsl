#version 330 core

layout(location = 0)in vec3 Position;
layout(location = 1)in vec3 Normal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec3 NormalFromView;
out vec3 PositionFromView;

void main()
{
    gl_Position = Projection*View*Model*vec4(Position, 1.f);
    PositionFromView = (View*Model*vec4(Position,1.f)).xyz;
    NormalFromView = (View*Model*vec4(Normal,0.f)).xyz;
}
