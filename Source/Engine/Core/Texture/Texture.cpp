#include "Texture.h"


Texture::Texture()
{
}

Texture::Texture(const char* image, GLenum slot, int isRGBA)
{
	this->slot = slot;
	int imgWidth, imgHeight, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(image, &imgWidth, &imgHeight, &nrChannels, 0);
	if (data)
	{
		glGenTextures(1, &ID);
		glActiveTexture(slot);
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (isRGBA == 0) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture\n";
	}
	stbi_image_free(data);
}

GLenum Texture::getFreeSlot()
{
	return GLenum();
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	GLuint texUni = glGetUniformLocation(shader.shaderID, uniform);
	shader.Actvate();
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(texType, ID);
}

void Texture::Unbind()
{
	glBindTexture(texType, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}