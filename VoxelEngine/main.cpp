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
#include "Input/Input.h"
#include "Rendering/Chunk.h"

////Function used to resize the window appropriately.
//void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
//void Mouse(GLFWwindow* window, double xPos, double yPos);

//Global screen settings.
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//Global camera variables.
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

//Global timing variables.
float deltaTime = 0.0f;         //Time difference of current frame and last frame.
float lastTime = 0.0f;          //Keeps track of the time of the last frame. Used to calculate deltaTime.

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "GLFW initialization failed." << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);  //4x antialiasing

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window;

    window = glfwCreateWindow(1280, 1024, "Window of the Gods!", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        std::cout << "GLFW window creation failed." << std::endl;
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //Added code
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);
    glfwSetCursorPosCallback(window, Mouse);

    //Tells GLFW to capture our mouse.
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //Check if GLEW is initialized
    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW failed to initialize." << std::endl;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //Compile and load shaders and store the program id
    GLuint programID = LoadShaders("Shaders/Vertex/CameraShader.vert", "Shaders/Fragment/SimpleFragmentShader.frag");

    //Prints the GLEW and openGL versions
    std::cout << "Using GLEW version :" << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "Using openGL version: " << glGetString(GL_VERSION) << std::endl;

    ///////TESTING
    //Block cube(BlockShapeIndex::Cube, false);
    Chunk* chunks[8];
    int index = 0;
    Chunk testChunk0(0, 0, 0);
    Chunk testChunk1(0, 0, 1);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                chunks[index++] = new Chunk(i, j, k);
            }
        }
    }

    //testChunk.GenerateTestChunk();
    //for (int x = 0; x < Chunk::renderDistance; x++)
    //{
    //   for (int y = 0; y < Chunk::renderDistance; y++)
    //    {
    //        for (int z = 0; z < Chunk::renderDistance; z++)
    //        {
    //            Chunk::loadedChunks[x][y][z].GenerateRandomChunk(x, y, z);
    //            Chunk::loadedChunks[x][y][z].BuildChunkMesh();
    //        }
    //    }
    //} 
    //
    //int size = Chunk::loadedChunks[1][1][1].GetChunkMesh().size() / 5;
    //
    //unsigned int VAO, VBO;
    //glGenVertexArrays(1, &VAO);
    //glBindVertexArray(VAO);
    //glGenBuffers(1, &VBO);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, Chunk::loadedChunks[1][1][1].GetChunkMesh().size() * sizeof(float), &Chunk::loadedChunks[1][1][1].GetChunkMesh()[0], GL_STATIC_DRAW);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);
    

    int width, height, nrChannels;
    unsigned char* data = stbi_load("Assets/Textures/TestTexture.png", &width, &height, &nrChannels, 0);
    if (!data)
    {
        std::cout << "Texture not loaded!" << std::endl;
    }
    unsigned int texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glGenerateMipmap(GL_TEXTURE_2D);

    delete data;

    double previousFPSTime = glfwGetTime();
    int frameCount = 0;
    bool isSorted = false;

    glUseProgram(programID);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
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
        ProcessInput(window, camera, deltaTime);

        /* Render here */
        glClearColor(0.0f, 0.0f, 0.5f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        //Pass the projection matrix to shader ( in this case could change every frame )
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glUniformMatrix4fv(glGetUniformLocation(programID, "projection"), 1, GL_FALSE, &projection[0][0]);

        //Camera view transformation.
        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(programID, "view"), 1, GL_FALSE, &view[0][0]);

        //Camera view transformation.
        glm::mat4 model = glm::mat4(1.0f);
        glUniformMatrix4fv(glGetUniformLocation(programID, "model"), 1, GL_FALSE, &model[0][0]);
        
        //Render multiple chunks
        for (int i = 0; i < index; i++)
        {
            chunks[i]->DrawChunk();
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDisableVertexAttribArray(0);
    glfwTerminate();
    return 0;
}

////Updates window when changed by OS or user. 
//void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
//{
//    //Make sure the viewport matches the new window dimensions.
//    glViewport(0, 0, width, height);
//}
//
//void Mouse(GLFWwindow* window, double xPos, double yPos)
//{
//    MouseCallback(window, xPos, yPos, camera);
//}

