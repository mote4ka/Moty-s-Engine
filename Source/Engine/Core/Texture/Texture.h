#pragma once

#include<glad/glad.h>
#include<stb/stb_image.h>

#include <iostream>
#include <string>

#include "../RHI/OpenGL/Shaders/ShaderClass/Shader.h"

class Texture {
public:
	GLuint ID;
	GLenum texType = GL_TEXTURE_2D;
	std::string FilePath;

	int ActiveSlot;
	Texture(const char* imagePath, int isRGBA);

	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();
private:

};