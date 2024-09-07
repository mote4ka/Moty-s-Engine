#pragma once

#include "cube.h"

#include "../RHI/OpenGL/Shaders/ShaderClass/Shader.h"

#include "../Camera/Camera.h"

#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

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
	void setPosition(glm::vec3 newPos);

	bool enable = true;

	glm::vec4 LightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	float LightColorF[4]{1.0f, 1.0f, 1.0f, 1.0f};
	glm::vec3 LightPos = glm::vec3(1.5f, 0.0f, 0.0f);
	glm::vec3 LightDirection = glm::vec3(-0.2f, -1.0f, -0.3f);
	Cube LightCube;

	glm::vec3 LightScale = glm::vec3(0.4f);

	//#########################################################
	//!!  VAO, VBO, EBO must be initialize after VAO.Bind()  !!
	//#########################################################
	VAO cubeVAO;
	VBO cubeVBO;
	EBO cubeEBO;

	static inline Camera* CameraRef;
	Shader lightShader{ "C:/Users/Матвей/source/repos/Moty's Engine/Source/Engine/Core/Light/shaders/light.vert", 
						"C:/Users/Матвей/source/repos/Moty's Engine/Source/Engine/Core/Light/shaders/light.frag" };
};