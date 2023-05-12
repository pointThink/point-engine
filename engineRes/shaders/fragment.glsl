#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_color;
uniform sampler2D u_texture;
uniform bool u_textured;

in vec2 v_texCoord;

void main()
{
	if (u_textured)
		color = texture2D(u_texture, v_texCoord) * u_color;

	else
		color = u_color;
}