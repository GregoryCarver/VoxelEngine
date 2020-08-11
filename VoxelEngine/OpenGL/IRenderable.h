#pragma once
class IRenderable
{
	//Might need to make these vectors, for each type of mesh(depending on textures) of an object(EX: chunks).
	unsigned int VAO, VBO;

public:
	void RenderableInit(int floatCount, std::vector<float>& meshVerts);
	unsigned int GetVAO();
	unsigned int GetVBO();
	void Draw(int vertCount);
};