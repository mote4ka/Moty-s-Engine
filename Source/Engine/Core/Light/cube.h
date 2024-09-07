#pragma once
#include "glad/glad.h"

#include "../RHI/OpenGL/Buffers/VAO.h"
#include "../RHI/OpenGL/Buffers/VBO.h"
#include "../RHI/OpenGL/Buffers/EBO.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

struct Cube {
public:
	GLfloat Vertices[64] =
	{ //     COORDINATES     //
		-0.5f,  0.0f,  0.5f,
		-0.5f,  0.0f, -0.5f,
		 0.5f,  0.0f, -0.5f,
		 0.5f,  0.0f,  0.5f,
		-0.5f,  1.0f,  0.5f,
		-0.5f,  1.0f, -0.5f,
		 0.5f,  1.0f, -0.5f,
		 0.5f,  1.0f,  0.5f
	};

	GLuint Indices[64] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
	};

	glm::mat4 model = glm::mat4(1.0f);

};