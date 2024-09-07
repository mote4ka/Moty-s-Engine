#pragma once

#include<glad/glad.h>
#include "GLFW/glfw3.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>


#include "../RHI/OpenGL/Shaders/ShaderClass/Shader.h"

class Camera {
public:
	glm::vec3 Position = glm::vec3(0.0f, 2.0f, 2.5f);
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 CameraMatrix = glm::mat4(1.0f);

	Camera(int windowWidth, int windowHeight);

	int width = 800, height = 600;

	bool firstClick = true;
	bool MovementActive = false;

	float normal_speed = 0.004f;
	float speed = normal_speed;
	float sensitivity = 60.0f;

	void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane);
	void Matrix(GLuint shaderID);
	void Inputs(GLFWwindow* window);
private:

};