#version 330 core
//in vec3 color;
in vec2 Texture;

out vec4 fragColor;

uniform sampler2D ourTexture;

void main()
{
	//fragColor = vec4(color, 1.0f);
	fragColor = texture(ourTexture, Texture);
}