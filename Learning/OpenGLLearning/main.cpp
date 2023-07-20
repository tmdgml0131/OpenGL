#include <stdio.h>
#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

// Window Dimensions
const GLint WIDTH = 800, HEIGHT = 600;

GLuint VAO, VBO, shader, uniformModel;

bool direction = true;
float triOffset = 0.0f;
float triMaxoffset = 0.9f;
float triIncrement = 0.05f;


// Vertex Shader
static const char* vShader = "														\n\
#version 330																		\n\
																					\n\
layout (location = 0) in vec3 pos;													\n\
																					\n\
uniform mat4 model;																	\n\
																					\n\
																					\n\
																					\n\
void main()																			\n\
{																					\n\
	gl_Position = model * vec4(pos.x, pos.y, pos.z, 1.0);							\n\
}																					\n\
";

// Fragment Shader
static const char* fShader = "							\n\
#version 330											\n\
														\n\
out vec4 color;											\n\
														\n\
void main()												\n\
{														\n\
	color = vec4(0.0, 1.0, 0.0, 1.0);					\n\
}														\n\
";

void CreateTriangle()
{
	GLfloat vertices[] = {
		-0.3f, -0.3f, 0.0f,
		0.3f, -0.3f, 0.0f,
		0.0f, 0.3f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, 1024, NULL, eLog);
		cout << "Error Compiling Program :" << shaderType << endl << eLog << endl;
		return;
	}
	
	glAttachShader(theProgram, theShader);
}

void CompileShaders()
{
	shader = glCreateProgram();

	if (!shader)
	{
		cout << "Shader Creation Failed!";
		return;
	}

	AddShader(shader, vShader, GL_VERTEX_SHADER);
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = {0};

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		cout << "Error Linking Program :" << eLog << endl;
		return;
	}

	glValidateProgram(shader);

	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		cout << "Error Validating Program :" << eLog << endl;
		return;
	}

	uniformModel = glGetUniformLocation(shader, "model");

}

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


	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Window Name", NULL, NULL);
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

	CreateTriangle();
	CompileShaders();


	// Loop until window closed
	while (!glfwWindowShouldClose(mainWindow))
	{
		// Get + Handle user input events
		glfwPollEvents();

		if (direction)
			triOffset += triIncrement;
		else
			triOffset -= triIncrement;

		if (abs(triOffset) >= triMaxoffset)
			direction = !direction;

		// Clear Window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);

		glm::mat4 model;
		model = glm::translate(model, glm::vec3(triOffset, 0.0f, 0.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);
	}


	return 0;
}