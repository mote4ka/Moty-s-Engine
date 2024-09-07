#pragma once

#include<glad/glad.h>
#include<stb/stb_image.h>

#include <iostream>

#include "../RHI/OpenGL/Shaders/ShaderClass/Shader.h"

class Texture {
public:
	GLuint ID;
	GLenum texType = GL_TEXTURE_2D;
	//GLenum format = GL_RGBA;
	//GLenum pixelType = GL_UNSIGNED_BYTE;
	GLenum slot;
	Texture();
	Texture(const char* image, GLenum slot, int isRGBA);

	static GLenum getFreeSlot();

	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();
private:

};