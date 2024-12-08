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
	if (Enable == true) {

		lightShader.Actvate();

		CameraRef->Matrix(lightShader.shaderID);

		glUniformMatrix4fv(glGetUniformLocation(lightShader.shaderID, "model"), 1, GL_FALSE, glm::value_ptr(LightCube.model));
		glUniform4f(glGetUniformLocation(lightShader.shaderID, "LightColor"), LightColor.x, LightColor.y, LightColor.z, LightColor.w);
		glUniform3f(glGetUniformLocation(lightShader.shaderID, "scale"), LightScale.x, LightScale.y, LightScale.z);

		//if (LightType != 0) {
			cubeVAO.Bind();
			glDrawElements(GL_TRIANGLES, sizeof(LightCube.Indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		//}
	}
}

void Light::SetLocation(glm::vec3 newPos)
{
	LightCube.model = glm::translate(LightCube.model, newPos - LightPos);
	LightPos = newPos;
	glUniformMatrix4fv(glGetUniformLocation(lightShader.shaderID, "model"), 1, GL_FALSE, glm::value_ptr(LightCube.model));
}

int Light::UpdateShadersUniform(GLuint ShaderID)
{
	if (Enable == true) {
		glUniform3f(glGetUniformLocation(ShaderID, "light.Position"), LightPos.x, LightPos.y, LightPos.z);
		glUniform3f(glGetUniformLocation(ShaderID, "light.Direction"), LightDirection.x, LightDirection.y, LightDirection.z);
		glUniform1i(glGetUniformLocation(ShaderID, "light.Type"), LightType);
		glUniform4f(glGetUniformLocation(ShaderID, "light.Color"), LightColor.x, LightColor.y, LightColor.z, LightColor.w);
		glUniform1f(glGetUniformLocation(ShaderID, "light.Power"), Power);
		glUniform3f(glGetUniformLocation(ShaderID, "light.ambient"), 0.01f, 0.01f, 0.01f);
		glUniform3f(glGetUniformLocation(ShaderID, "light.diffuse"), 0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(ShaderID, "light.specular"), 1.0f, 1.0f, 1.0f);
	}
	else {
		glUniform4f(glGetUniformLocation(ShaderID, "LightColor"), 0.0f, 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(ShaderID, "light.ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(ShaderID, "light.diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(ShaderID, "light.specular"), 0.0f, 0.0f, 0.0f);
	}

	return 0;
}
