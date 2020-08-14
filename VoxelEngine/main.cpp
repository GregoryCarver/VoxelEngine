//WORKING ON LOADING MULTIPLE CHUNKS

#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>

#include "OpenGL/OpenGLInitializer.h"
#include "Shaders/Functions/loadShader.h"
#include "Libraries/stb_image.h"
#include "Camera.h"
#include "Rendering/Chunk.h"
#include "OpenGL/OpenGLInitializer.h"

//Global screen settings.
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//Global timing variables.
float deltaTime = 0.0f;         //Time difference of current frame and last frame.
float lastTime = 0.0f;          //Keeps track of the time of the last frame. Used to calculate deltaTime.

int main(void)
{
    OpenGLInitializer glObject;

    //Compile and load shaders and store the program id
    GLuint programID = LoadShaders("Shaders/Vertex/CameraShader.vert", "Shaders/Fragment/SimpleFragmentShader.frag");

    ///////TESTING
    //Block cube(BlockShapeIndex::Cube, false);
    int cd = 2;
    Chunk* chunks[8];
    int index = 0;
    Chunk testChunk0(0, 0, 0);
    Chunk testChunk1(0, 0, 1);
    for (int i = 0; i < cd; i++)
    {
        for (int j = 0; j < cd; j++)
        {
            for (int k = 0; k < cd; k++)
            {
                chunks[index++] = new Chunk(i, j, k);
            }
        }
    }

    int width, height, nrChannels;
    unsigned char* data = stbi_load("Assets/Textures/testdirt.png", &width, &height, &nrChannels, 0);
    if (!data)
    {
        std::cout << "Texture not loaded!" << std::endl;
    }
    unsigned int texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glGenerateMipmap(GL_TEXTURE_2D);

    delete data;

    double previousFPSTime = glfwGetTime();
    int frameCount = 0;
    bool isSorted = false;

    glUseProgram(programID);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(glObject.GetWindow()))
    {
        //Get the time variables and display fps
        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        frameCount++;
        if (currentTime - previousFPSTime >= 1.0f)
        {
            std::cout << "FPS: " << frameCount << "\r";
            frameCount = 0;
            previousFPSTime = currentTime;
        }

        //Input
        glObject.ProcessInput(glObject.GetWindow(), glObject.GetCamera(), deltaTime);
        
        glObject.ClearWindow();

        //Pass the projection matrix to shader ( in this case could change every frame )
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glUniformMatrix4fv(glGetUniformLocation(programID, "projection"), 1, GL_FALSE, &projection[0][0]);

        //Camera view transformation.
        glm::mat4 view = glObject.GetCamera().GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(programID, "view"), 1, GL_FALSE, &view[0][0]);

        //Camera view transformation.
        glm::mat4 model = glm::mat4(1.0f);
        glUniformMatrix4fv(glGetUniformLocation(programID, "model"), 1, GL_FALSE, &model[0][0]);
        
        //Render multiple chunks
        for (int i = 0; i < index; i++)
        {
            chunks[i]->DrawChunk();
        }

        glObject.EventPoll();
    }

    glDisableVertexAttribArray(0);
    glfwTerminate();
    return 0;
}