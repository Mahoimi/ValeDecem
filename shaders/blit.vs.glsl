#version 330 core

layout(location=0)in vec2 Position;

out vec2 v_UV;

void main(void)
{	
	v_UV = Position * 0.5 + 0.5;
	gl_Position = vec4(Position.xy, 0.0, 1.0);
}
