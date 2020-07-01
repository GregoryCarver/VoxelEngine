#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>

#include "Shaders/Functions/loadShader.h"
#include "Libraries/stb_image.h"

int main(void)
{
    //////TEXTURE TEST
    /*int width, height, nrChannels;
    unsigned char* data = stbi_load("Assets/Textures/TestTexture.png", &width, &height, &nrChannels, 0);

    unsigned int texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);*/

    //////TEST END

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
    GLuint programID = LoadShaders("Shaders/Vertex/SimpleVertexShader.vert", "Shaders/Fragment/SimpleFragmentShader.frag");

    //Prints the GLEW and openGL versions
    std::cout << "Using GLEW version :" << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "Using openGL version: " << glGetString(GL_VERSION) << std::endl;

    GLfloat triangleBuffer[] =
    {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f
    };
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleBuffer), triangleBuffer, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

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
    glGenerateMipmap(GL_TEXTURE_2D);


    double previousFPSTime = glfwGetTime();
    int frameCount = 0;
    bool isSorted = false;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        //Get the time variables and display fps
        /*float currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        frameCount++;
        if (currentTime - previousFPSTime >= 1.0f)
        {
            std::cout << "FPS: " << frameCount << "\r";
            frameCount = 0;
            previousFPSTime = currentTime;
        }*/

        //Input
        //ProcessInput(window, camera, deltaTime);

   
        /* Render here */
        glClearColor(0.0f, 0.0f, 0.5f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //Added code
        glUseProgram(programID);
        

        //Pass the projection matrix to shader ( in this case could change every frame )
        //glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glUniformMatrix4fv(glGetUniformLocation(programID, "projection"), 1, GL_FALSE, &projection[0][0]);

        ////Camera/view transformation.
        //glm::mat4 view = camera.GetViewMatrix();
        //glUniformMatrix4fv(glGetUniformLocation(programID, "view"), 1, GL_FALSE, &view[0][0]);

        //glBindVertexArray(cube.GetVAO());
        //glDrawArraysInstanced(GL_TRIANGLES, 0, 36, cubeGridXCoord * cubeGridYCoord * cubeGridZCoord);
        //glBindVertexArray(0);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

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