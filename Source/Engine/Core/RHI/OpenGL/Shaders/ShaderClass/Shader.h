#pragma once
#include "glad/glad.h"
#include "getFileContent.cpp"
#include <string>

class Shader {
public:
	GLuint shaderID;
	Shader(const char* VertShaderPath, const char* FragShaderPath);
	void Create();
	void ReloadShaders();
	void Actvate();
	void Delete();
private:
	std::string VertShaderPath, FragShaderPath;
};