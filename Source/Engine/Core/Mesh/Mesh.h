#pragma once
#include <glad/glad.h>
#include <iostream>

#include "../RHI/OpenGL/Shaders/ShaderClass/Shader.h"

#include "../RHI/OpenGL/Buffers/VAO.h"
#include "../RHI/OpenGL/Buffers/VBO.h"
#include "../RHI/OpenGL/Buffers/EBO.h"

#include "../Texture/Texture.h"

#include "../Camera/Camera.h"

#include "../Light/Light.h"

#include <filesystem>



class Mesh {
public:

	Mesh(std::string vertFile = "default.vert", std::string fragFile = "default.frag", bool CreateTexture = true);
	~Mesh();
	static void setCameraRef(Camera* CameraRefInpt);

	void Draw();

	// setTransform doesnt work correctly!!
	void setLocation(glm::vec3 newLocation);

	void addLocation(glm::vec3 newLocation);

	//void setAxisLocation(glm::vec3)
	void setLocationX(float x);

	void setRotation(glm::vec3 newRotation);
	void addRotation(glm::vec3 newRotation);

	void setScale(glm::vec3 newScale);

	Light* lightsRef;

	//this shit without "inline" give lnk2001, idk why
	static inline Camera* CameraRef;

private:
	GLfloat vertices[512] =
	{
		//     COORDINATES     /        COLORS      /   TexCoord  //	     NORMALS	//
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		 0.5f, 0.0f, -0.5f,		0.83f, 0.70f, 0.44f,	1.0f, 1.0f,		0.0f, -1.0f, 0.0f,

		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,		0.0f,  0.0f,-1.0f,
		-0.5f, 1.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 1.0f,		0.0f,  0.0f,-1.0f,
		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,		0.0f,  0.0f,-1.0f,
		 0.5f, 1.0f, -0.5f,		0.83f, 0.70f, 0.44f,	1.0f, 1.0f,		0.0f,  0.0f,-1.0f,

		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,		0.0f,  0.0f,1.0f,
		 0.5f, 1.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 1.0f,		0.0f,  0.0f,1.0f,
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,		0.0f,  0.0f,1.0f,
		-0.5f, 1.0f,  0.5f,	    0.83f, 0.70f, 0.44f,	1.0f, 1.0f,		0.0f,  0.0f,1.0f,

		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,	   -1.0f,  0.0f, 0.0f,
		-0.5f, 1.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 1.0f,	   -1.0f,  0.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,	   -1.0f,  0.0f, 0.0f,
		-0.5f, 1.0f, -0.5f,		0.83f, 0.70f, 0.44f,	1.0f, 1.0f,	   -1.0f,  0.0f, 0.0f,
		
		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
		 0.5f, 1.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 1.0f,		1.0f, 0.0f, 0.0f,
		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,		1.0f, 0.0f, 0.0f,
		 0.5f, 1.0f,  0.5f,		0.83f, 0.70f, 0.44f,	1.0f, 1.0f,		1.0f, 0.0f, 0.0f,

		-0.5f, 1.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,		0.0f,  1.0f, 0.0f,
		-0.5f, 1.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 1.0f,		0.0f,  1.0f, 0.0f,
		 0.5f, 1.0f, -0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,		0.0f,  1.0f, 0.0f,
		 0.5f, 1.0f,  0.5f,		0.83f, 0.70f, 0.44f,	1.0f, 1.0f,		0.0f,  1.0f, 0.0f,
	};
	GLuint indices[128] =
	{
		//BOTTOM
		0, 1, 2,
		1, 2, 3,
		//FRONT
		4, 5, 6,
		5, 6, 7,
		//BACK
		8, 9, 10,
		9, 10, 11,
		//LEFT
		12, 13, 14,
		13, 14, 15,
		//RIGHT
		16, 17, 18,
		17, 18, 19,
		//UP
		20, 21, 22,
		21, 22, 23,
	};

	GLuint uniID;

	std::string DirPath = (std::filesystem::current_path()).string();
	std::string shaderPath = DirPath + std::string("/Source/Engine/Core/RHI/OpenGL/Shaders/");
	std::string texturePath = DirPath + std::string("/Source/Engine/Core/Texture/img/");
	std::string vertFile = "default.vert";
	std::string fragFile = "default.frag";



public: Shader MeshShader{ (shaderPath + vertFile).c_str(),
						   (shaderPath + fragFile).c_str() };
private:
	VAO MeshVAO;
	VBO MeshVBO;
	EBO MeshEBO;

	glm::vec3 Location = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 Rotation = glm::vec3(0.0f, 0.0f, 0.0f);

	GLuint modelLoc;
	glm::mat4 model = glm::mat4(1.0f);

public:
	int texNum = 0;
	glm::vec2 uv = glm::vec2(1.0f, 1.0f);
private:
	Texture BaseTex{ (texturePath + std::string("container_d.png")).c_str(), GL_TEXTURE0, 1 };
	Texture RoughnessTex{ (texturePath + std::string("container_r.png")).c_str(), GL_TEXTURE1, 1};
	
};