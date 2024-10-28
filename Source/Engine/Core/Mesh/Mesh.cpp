#include "Mesh.h"

Mesh::Mesh(std::string vertFile, std::string fragFile, bool CreateTexture)
{
	this->vertFile = vertFile;
	this->fragFile = fragFile;
	MeshVAO.Bind();

	VBO MeshVBO{ vertices, sizeof(vertices) };
	EBO MeshEBO{ indices, sizeof(indices) };

	MeshVAO.LinkAttrib(MeshVBO, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	MeshVAO.LinkAttrib(MeshVBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	MeshVAO.LinkAttrib(MeshVBO, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	MeshVAO.LinkAttrib(MeshVBO, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	MeshVAO.Unbind();
	MeshVBO.Unbind();
	MeshEBO.Unbind();

	modelLoc = glGetUniformLocation(MeshShader.shaderID, "model");
	model = glm::translate(model, Location);
	model = glm::rotate(model, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	std::cout << "Mesh created!\n";
}

Mesh::~Mesh()
{
	MeshShader.Delete();
	MeshVAO.Delete();
	MeshVBO.Delete();
	MeshEBO.Delete();
	BaseTex.Delete();
}

void Mesh::setCameraRef(Camera* CameraRefInpt)
{
	CameraRef = CameraRefInpt;
}

void Mesh::Draw()
{
	MeshShader.Actvate();

	CameraRef->Matrix(MeshShader.shaderID);
	
	//Mesh unis
	glUniform3f(glGetUniformLocation(MeshShader.shaderID, "Rotation"), Rotation.x, Rotation.y, Rotation.z);
	glUniform2f(glGetUniformLocation(MeshShader.shaderID, "uv"), uv.x, uv.y);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	//Cam uni
	glUniform3f(glGetUniformLocation(MeshShader.shaderID, "CamPos"), CameraRef->Position.x, CameraRef->Position.y, CameraRef->Position.z);

	//Material unis
	glUniform3f(glGetUniformLocation(MeshShader.shaderID, "mat.diffuse"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(MeshShader.shaderID, "mat.specular"), 0.5f, 0.5f, 0.5f);
	glUniform1f(glGetUniformLocation(MeshShader.shaderID, "mat.shineFac"), 0.5f);

	//Light unis
	if (lightsRef != nullptr) {
		if (lightsRef->enable == true) {
			glUniform1i(glGetUniformLocation(MeshShader.shaderID, "LightType"), lightsRef->LightType);
			glUniform4f(glGetUniformLocation(MeshShader.shaderID, "LightColor"), lightsRef->LightColorF[0], lightsRef->LightColorF[1], lightsRef->LightColorF[2], lightsRef->LightColorF[3]);
			glUniform3f(glGetUniformLocation(MeshShader.shaderID, "light.Position"), lightsRef->LightPos.x, lightsRef->LightPos.y, lightsRef->LightPos.z);
			glUniform3f(glGetUniformLocation(MeshShader.shaderID, "light.Direction"), lightsRef->LightDirection.x, lightsRef->LightDirection.y, lightsRef->LightDirection.z);
			glUniform3f(glGetUniformLocation(MeshShader.shaderID, "light.ambient"), 0.15f, 0.15f, 0.15f);
			glUniform3f(glGetUniformLocation(MeshShader.shaderID, "light.diffuse"), 0.5f, 0.5f, 0.5f);
			glUniform3f(glGetUniformLocation(MeshShader.shaderID, "light.specular"), 1.0f, 1.0f, 1.0f);
		}
		else {
			glUniform4f(glGetUniformLocation(MeshShader.shaderID, "LightColor"), 0.0f, 0.0f, 0.0f, 0.0f);
		}
	}
	RoughnessTex.texUnit(MeshShader, "mat.specular", 1);
	RoughnessTex.Bind();
	BaseTex.texUnit(MeshShader, "mat.BaseColor", 0);
	BaseTex.Bind();

	MeshVAO.Bind();
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
}

void Mesh::setLocation(glm::vec3 newLocation)
{
	glm::vec3 dif = newLocation - Location;
	Location += dif;
	model = glm::translate(model, dif);
	MeshShader.Actvate();
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 
}

void Mesh::setRotation(glm::vec3 newRotation)
{
	glm::vec3 dif = newRotation - Rotation;
	Rotation += dif;
	model = glm::rotate(model, glm::radians(dif.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(dif.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(dif.z), glm::vec3(0.0f, 0.0f, 1.0f));
	MeshShader.Actvate();
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}

void Mesh::setDeltaRotation(glm::vec3 newRotation)
{
	Rotation += newRotation;
	model = glm::rotate(model, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}

void Mesh::setScale(glm::vec3 newScale)
{
	Scale = newScale;
	model[0].x = newScale.x;
	model[1].y = newScale.y;
	model[2].z = newScale.z;
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}
