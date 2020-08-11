#pragma once
#include <glew.h>
#include <glfw3.h>
#include <../Camera.h>

class OpenGLInitializer
{
	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window;
	static Camera camera;

	//Function used to resize the window appropriately.
	OpenGLInitializer();
	static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
	static void Mouse(GLFWwindow* window, double xPos, double yPos);
};