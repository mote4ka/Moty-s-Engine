#pragma once

#include "cube.h"

#include "../RHI/OpenGL/Shaders/ShaderClass/Shader.h"

#include "../Camera/Camera.h"

#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "filesystem"
#include <iostream>

#define DIRECTIONAL 0;
#define POINT 1;
#define SPOT 2;

class Light {

public:
	Light();

	void Draw();

	int LightType = POINT;
	//Doesnt work!! Need to fix
	void SetPosition(glm::vec3 newPos);
	void GetPosition();

	int UpdateShadersUniform(GLuint ShaderID);

	bool Enable = true;

	glm::vec4 LightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 LightPos = glm::vec3(1.5f, 0.0f, 0.0f);
	glm::vec3 LightDirection = glm::vec3(0.4f, -1.0f, -3.0f);
	float Power = 1.5f;

	Cube LightCube;
	glm::vec3 LightScale = glm::vec3(0.4f);

	//#########################################################
	//!!  VAO, VBO, EBO must be initialize after VAO.Bind()  !!
	//#########################################################
	VAO cubeVAO;
	VBO cubeVBO;
	EBO cubeEBO;

	static inline Camera* CameraRef;
	std::string DirPath = (std::filesystem::current_path()).string();
	std::string shaderPath = DirPath + std::string("/Source/Engine/Core/Light/shaders/");
	std::string vertFile = "light.vert";
	std::string fragFile = "light.frag";
	Shader lightShader{ (shaderPath + vertFile).c_str(),
						 (shaderPath + fragFile).c_str() };
};