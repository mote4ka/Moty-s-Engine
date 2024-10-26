#include "Light.h"

Light::Light()
{
	cubeVAO.Bind();

	VBO cubeVBO{ LightCube.Vertices, sizeof(LightCube.Vertices) };
	EBO cubeEBO{ LightCube.Indices, sizeof(LightCube.Indices) };

	cubeVAO.LinkAttrib(cubeVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	cubeVAO.Unbind();
	cubeVBO.Unbind();
	cubeEBO.Unbind();

	//LightCube.model = glm::scale(LightCube.model, LightScale);
	LightCube.model = glm::translate(LightCube.model, LightPos);

	std::cout << "Let there be light!\n";
}

void Light::Draw()
{
	if (enable == true) {

		lightShader.Actvate();

		CameraRef->Matrix(lightShader.shaderID);

		glUniformMatrix4fv(glGetUniformLocation(lightShader.shaderID, "model"), 1, GL_FALSE, glm::value_ptr(LightCube.model));
		glUniform4f(glGetUniformLocation(lightShader.shaderID, "LightColor"), LightColorF[0], LightColorF[1], LightColorF[2], LightColorF[3]);
		glUniform3f(glGetUniformLocation(lightShader.shaderID, "scale"), LightScale.x, LightScale.y, LightScale.z);

		//if (LightType != 0) {
			cubeVAO.Bind();
			glDrawElements(GL_TRIANGLES, sizeof(LightCube.Indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		//}
	}
}

void Light::setPosition(glm::vec3 newPos)
{
	LightPos = newPos - LightPos;
	LightCube.model = glm::translate(LightCube.model, LightPos);
}
