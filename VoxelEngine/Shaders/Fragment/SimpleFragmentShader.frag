#version 330 core
//in vec3 color;
in vec2 Texture;

out vec4 fragColor;

uniform sampler2D ourTexture;

void main()
{
	//fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	fragColor = texture(ourTexture, Texture);
}