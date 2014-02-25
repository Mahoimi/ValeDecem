#version 330 core

layout(location = 0)in vec3 Position;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

out vec3 v_UV;

void main(){
    gl_Position = (Projection * View * Model * vec4(Position, 1.0)).xyww;
    v_UV = Position;
}
