#version 330 core

layout(location = 0) out vec4 o_Color;

in vec4 v_Color;

void main()
{
	//color = u_Color;
	o_Color = v_Color;
};