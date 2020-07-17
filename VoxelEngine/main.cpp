#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>

#include "Shaders/Functions/loadShader.h"
#include "Libraries/stb_image.h"
#include "Camera.h"
#include "Input/Input.h"
//#include "Rendering/Block.h"
#include "Rendering/Chunk.h"

//Function used to resize the window appropriately.
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
inline void Mouse(GLFWwindow* window, double xPos, double yPos);

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

    //Triangle doesn't show if other 3 are uncommented
    glfwWindowHint(GLFW_SAMPLES, 4);                                    //4x antialiasing
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                      //OpenGL 3.3
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);      //We don't want the old OpenGL
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    /*       OpenGLtutorials.org tutorial end       */

    GLFWwindow* window;

    /* Create a windowed mode window and its OpenGL context */
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

    //Compile and load shaders and store the program id
    GLuint programID = LoadShaders("Shaders/Vertex/CameraShader.vert", "Shaders/Fragment/SimpleFragmentShader.frag");

    //Prints the GLEW and openGL versions
    std::cout << "Using GLEW version :" << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "Using openGL version: " << glGetString(GL_VERSION) << std::endl;

    GLfloat triangleBuffer[] =
    {   //Positions            //Texture
         -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
          0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

         -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
          0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
          0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
          0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
          0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
          0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    ///////TESTING
    //Block cube(BlockShapeIndex::Cube, false);
    Chunk testChunk;
    testChunk.GenerateTestChunk();
    testChunk.BuildChunkMesh();
    /*for (int i = 0; i < testChunk.GetChunkMesh().size();)
    {
        std::cout << testChunk.GetChunkMesh()[i++] << " " << testChunk.GetChunkMesh()[i++] << " " << testChunk.GetChunkMesh()[i++] << std::endl;
    }
    return 0;*/

    GLfloat textureBuffer[] =
    {
        //Texture
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };
    int size = 72 * testChunk.GetChunkMesh().size() / 18 / 6;
    float* newTex =  new float[size];
    
    for (int i = 0; i < size;)
    {
        for (int j = 0; j < 72; j++)
        {
            newTex[i++] = textureBuffer[j];
        }
    }
    /*std::vector<float> allFaces;
    allFaces.reserve(cube.GetBlockShape().GetBackFace().size() * 6);
    allFaces.insert(allFaces.end(), cube.GetBlockShape().GetFrontFace().begin(), cube.GetBlockShape().GetFrontFace().end());
    allFaces.insert(allFaces.end(), cube.GetBlockShape().GetLeftFace().begin(), cube.GetBlockShape().GetLeftFace().end());
    allFaces.insert(allFaces.end(), cube.GetBlockShape().GetBackFace().begin(), cube.GetBlockShape().GetBackFace().end());
    allFaces.insert(allFaces.end(), cube.GetBlockShape().GetRightFace().begin(), cube.GetBlockShape().GetRightFace().end());
    allFaces.insert(allFaces.end(), cube.GetBlockShape().GetTopFace().begin(), cube.GetBlockShape().GetTopFace().end());
    allFaces.insert(allFaces.end(), cube.GetBlockShape().GetBottomFace().begin(), cube.GetBlockShape().GetBottomFace().end());*/

    ///////END

    unsigned int VAO, VBO, VBO2;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, testChunk.GetChunkMesh().size() * sizeof(float), &testChunk.GetChunkMesh()[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), newTex, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(1);
    
    int width, height, nrChannels;
    unsigned char* data = stbi_load("Assets/Textures/TestTexture.png", &width, &height, &nrChannels, 0);
    if (!data)
    {
        std::cout << "WHY!?" << std::endl;
    }
    unsigned int texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);

    delete data;

    double previousFPSTime = glfwGetTime();
    int frameCount = 0;
    bool isSorted = false;

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


        //Added code
        glUseProgram(programID);
        

        //Pass the projection matrix to shader ( in this case could change every frame )
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glUniformMatrix4fv(glGetUniformLocation(programID, "projection"), 1, GL_FALSE, &projection[0][0]);

        //Camera view transformation.
        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(programID, "view"), 1, GL_FALSE, &view[0][0]);

        //Camera view transformation.
        glm::mat4 model = glm::mat4(1.0f);
        glUniformMatrix4fv(glGetUniformLocation(programID, "model"), 1, GL_FALSE, &model[0][0]);

        //glBindVertexArray(cube.GetVAO());
        //glDrawArraysInstanced(GL_TRIANGLES, 0, 36, cubeGridXCoord * cubeGridYCoord * cubeGridZCoord);
        //glBindVertexArray(0);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, size * 36);

        //Added code end

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDisableVertexAttribArray(0);
    glfwTerminate();
    return 0;
}

//Updates window when changed by OS or user. 
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    //Make sure the viewport matches the new window dimensions.
    glViewport(0, 0, width, height);
}

inline void Mouse(GLFWwindow* window, double xPos, double yPos)
{
    MouseCallback(window, xPos, yPos, camera);
}