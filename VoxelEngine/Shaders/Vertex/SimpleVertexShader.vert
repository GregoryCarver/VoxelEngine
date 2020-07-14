#version 330 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main()
{
	gl_Position.xyz = aPosition;
	gl_Position.w = 1.0;
	TexCoord = aTexCoord;
}