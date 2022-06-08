#version 450 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec3 a_Color;
layout(location = 2) in float a_Opacity;
layout(location = 3) in vec2 a_TexCoord;

uniform mat4 u_ViewProj;
uniform mat4 u_Transform;

out vec3 v_Color;
out vec2 v_TexCoord;
out float v_Opacity;

void main()
{
	gl_Position = u_ViewProj * u_Transform * vec4(a_Position, 0.0f, 1.0);
	v_Color = a_Color;
	v_Opacity = a_Opacity;
	v_TexCoord = a_TexCoord;
}