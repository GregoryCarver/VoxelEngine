#include <iostream>
#include <stdlib.h>
#include "OpenGLInitializer.h"
#include "../Input/Input.h"

//Updates window when changed by OS or user. 
void OpenGLInitializer::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    //Make sure the viewport matches the new window dimensions.
    glViewport(0, 0, width, height);
}

void OpenGLInitializer::Mouse(GLFWwindow* window, double xPos, double yPos)
{
    MouseCallback(window, xPos, yPos, camera);
}

OpenGLInitializer::OpenGLInitializer()
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "GLFW initialization failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_SAMPLES, 4);  //4x antialiasing

	window = glfwCreateWindow(1280, 1024, "Window of the Gods!", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        std::cout << "GLFW window creation failed." << std::endl;
        exit(EXIT_FAILURE);
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

    //Prints the GLEW and openGL versions
    std::cout << "Using GLEW version :" << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "Using openGL version: " << glGetString(GL_VERSION) << std::endl;
}