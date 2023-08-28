#pragma once
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <GL/glew.h>

class Shader
{
public:
	Shader();

	void CreateFromString(const char* vertextCode, const char* fragmentCode);

	void CreateFromFiles(const char* vertextLocation, const char* fragmentLocation);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();

	std::string ReadFile(const char* fileLocation);

	void UseShader();
	void ClearShader();

	~Shader();

private:
	GLuint shaderID, uniformProjection, uniformModel;
	
	void CompileShader(const char* vertextCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

