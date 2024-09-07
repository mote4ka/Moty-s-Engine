#include "Shader.h"

Shader::Shader(const char* VertShaderPath, const char* FragShaderPath)
{
	std::string vertexCodeStr = getFileContent(VertShaderPath);
	const char* vertexCode = vertexCodeStr.c_str();
	std::string fragCodeStr = getFileContent(FragShaderPath);
	const char* fragCode = fragCodeStr.c_str();


	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexCode, NULL);
	glCompileShader(vertexShader);

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragCode, NULL);
	glCompileShader(fragShader);

	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragShader);
	glLinkProgram(shaderID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
}

void Shader::Actvate()
{
	glUseProgram(shaderID);
}

void Shader::Delete()
{
	glDeleteProgram(shaderID);
}
