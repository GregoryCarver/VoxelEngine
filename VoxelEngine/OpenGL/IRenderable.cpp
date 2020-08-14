#include <glew.h>
#include <glfw3.h>
#include <vector>
#include "IRenderable.h"


void IRenderable::RenderableInit(int floatCount, std::vector<float>& meshVerts)
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, floatCount * sizeof(float), &meshVerts[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

unsigned int IRenderable::GetVAO()
{
    return VAO;
}

unsigned int IRenderable::GetVBO()
{
    return VBO;
}

void IRenderable::Draw(int vertCount)
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertCount);
}