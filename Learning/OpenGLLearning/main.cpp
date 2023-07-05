#include <stdio.h>
#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const GLint WIDTH = 1800, HEIGHT = 1600;

using namespace std;


int main()
{
	// GLFW 시작
	if (!glfwInit())
	{
		cout << ("GLFW 시작 실패");
		glfwTerminate();
		return 1;
	}
	
	// GLFW Window Properties SetUp
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile = No Backwards Compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  
	// Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		cout << "GLFW Window Creation Failed";
		glfwTerminate();
		return 1;
	}
		
	// Get Buffer Size Information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set Context for GLEW to Use
	glfwMakeContextCurrent(mainWindow);

	// Allow Modern Extension Features
	glewExperimental = GL_TRUE;

	
	if (glewInit() != GLEW_OK)
	{
		cout << ("GLEW 시작 실패");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Setup Viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	// Loop until window closed
	while (!glfwWindowShouldClose(mainWindow))
	{
		// Get + Handle user input events
		glfwPollEvents();

		// Clear Window
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(mainWindow);
	}


	return 0;
}