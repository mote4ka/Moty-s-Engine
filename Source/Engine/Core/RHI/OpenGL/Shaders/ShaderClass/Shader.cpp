#include "Shader.h"

Shader::Shader(const char* VertShaderPath, const char* FragShaderPath)
{
	this->VertShaderPath = VertShaderPath;
	this->FragShaderPath = FragShaderPath;
	
	Create();
}

void Shader::Create()
{
	std::string vertexCodeStr = Content::GetFileContent(VertShaderPath.c_str());
	const char* vertexCode = vertexCodeStr.c_str();
	std::string fragCodeStr = Content::GetFileContent(FragShaderPath.c_str());
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

void Shader::ReloadShaders()
{
	Delete();
	Create();
}

void Shader::Actvate()
{
	glUseProgram(shaderID);
}

void Shader::Delete()
{
	glDeleteProgram(shaderID);
}
