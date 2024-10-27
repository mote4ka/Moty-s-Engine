#include <filesystem>

#include "../Engine/Core/Window/Window.h"
#include "../Engine/Core/RHI/OpenGL/Shaders/ShaderClass/Shader.h"
#include "../Engine/Core/Mesh/Mesh.h"
#include "../Engine/Core/Camera/Camera.h"

#include"../Engine/Core/Light/Light.h"

#include "../UI/imgui/imgui.h"
#include "../UI/UI.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


class App {
public:
	void Run() {
		Window win;
		win.Open();

		Camera cam(win.getWindowWidth(), win.getWindowHeight());
		
		Mesh cube1;
		//cube1.texNum = 1;
		cube1.setLocation(glm::vec3(0.0f, 0.0f, 0.0f));

		cube1.setCameraRef(&cam);
		
		Light light1;
		light1.CameraRef = &cam;

		cube1.lightsRef = &light1;

		UI ui(&win, &cam);
		ImGui::LoadStyles();
		ImGui::LoadColors();

		float loc[3] = { 0.0f, 0.0f, 0.0f };
		float rot[3] = { 0.0f, 0.0f, 0.0f };
		float sc[3] = { 1.0f, 1.0f, 1.0f };

		glEnable(GL_DEPTH_TEST);

		while (!win.WindowShouldClose()) {

			glClearColor(0.20f, 0.20f, 0.20f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			if (glfwGetKey(win.getWindowRef(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				win.Close();
			}
			if (glfwGetKey(win.getWindowRef(), GLFW_KEY_F1) == GLFW_PRESS) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			if (glfwGetKey(win.getWindowRef(), GLFW_KEY_F2) == GLFW_PRESS) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}

			cam.Inputs(win.getWindowRef());

			cam.UpdateMatrix(45.0f, 0.1f, 100.0f);

			//UI things
			ui.NewFrame();

			//ImGui::SetNextWindowSize({ 250.f,368.f });
			//ImGui::SetCursorPos({ 0.0f,0.0f });
			ImGui::Begin("Properties");
			ImGui::SetCursorPos({ 15.0f, 30.0f });
			ImGui::Checkbox("Light", &light1.enable);
			ImGui::SetCursorPos({ 15.0f, 60.0f });
			//ImGui::PushItemWidth(120.0f);
			ImGui::ColorEdit4("Color", light1.LightColorF);
			//ImGui::PopItemWidth();
			//ImGui::SetCursorPos({ 15.0f, 90.0f });
			//ImGui::PushItemWidth(120.0f);
			ImGui::DragFloat3("Location", loc, 0.1f);
			ImGui::DragFloat3("Rotation", rot, 0.1f);
			ImGui::DragFloat3("Scale", sc, 0.1f);
			if (ImGui::Button("Reload Shaders")) {
				cube1.MeshShader.ReloadShaders();
			}
			ImGui::End();

			cube1.setLocation(glm::vec3(loc[0], loc[1], loc[2]));
			cube1.setRotation(glm::vec3(rot[0], rot[1], rot[2]));
			cube1.setScale(glm::vec3(sc[0], sc[1], sc[2]));

			glUniform3f(glGetUniformLocation(cube1.MeshShader.shaderID, "CamPos"), cam.Position.x, cam.Position.y, cam.Position.z);

			//Draw
			cube1.Draw();
			light1.Draw();

			ui.Draw();

			win.SwapBufers();
		}
	}

};