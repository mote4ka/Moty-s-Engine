#pragma once
#include <glad/glad.h>

struct VBO {
	GLuint ID;

	VBO();
	VBO(GLfloat* vertices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};