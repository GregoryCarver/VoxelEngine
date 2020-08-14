#pragma once
#include <glew.h>
#include <glfw3.h>
#include <../Camera.h>

class OpenGLInitializer
{
	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window;
	static Camera camera;

public:
	//Function used to resize the window appropriately.
	OpenGLInitializer();
	void ClearWindow();
	void EventPoll();
	static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
	static void Mouse(GLFWwindow* window, double xPos, double yPos);
	//Function to get mouse location and process mouse input.
	static void MouseCallback(GLFWwindow* window, double xPos, double yPos, Camera& camera);
	//Function to process the input of the keyboard.
	void ProcessInput(GLFWwindow* window, Camera& camera, float& deltaTime);
	Camera& GetCamera();
	GLFWwindow* GetWindow();
};