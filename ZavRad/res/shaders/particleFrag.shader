#version 450 core

layout(location = 0) out vec4 o_Color;

in vec3 v_Color;
in float v_Opacity;
in vec2 v_TexCoord;
uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	//o_Color = v_Color;
	texColor.r = v_Color.r;
	texColor.g = v_Color.g;
	texColor.b = v_Color.b;
	texColor.a = texColor.a * v_Opacity;
	o_Color = texColor;
}