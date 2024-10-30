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
		Mesh cube2;
		cube1.SetLocation(glm::vec3(0.0f, 0.0f, 0.0f));
		cube2.SetLocation(glm::vec3(1.5f, -1.0f, 0.0f));
		cube2.SetScale(glm::vec3(10.f, 0.5f, 10.0f));

		cube1.SetCameraRef(&cam);
		cube2.SetCameraRef(&cam);
		
		Light light1;
		light1.CameraRef = &cam;

		cube1.LightsRef = &light1;
		cube2.LightsRef = &light1;

		cube1.SetTexture("bp/bp_d.png", "bp/bp_r.png");
		cube2.SetTexture("garage_floor_d.png", "garage_floor_r.png");

		UI ui(&win, &cam);
		ImGui::LoadStyles();
		ImGui::LoadColors();

		//temporally varies
		float loc[3] = { 0.0f, 0.0f, 0.0f };
		float rot[3] = { 0.0f, 0.0f, 0.0f };
		float sc[3] = { 1.0f, 1.0f, 1.0f };
		float cl[4] = { 1.0f, 1.0f, 1.0f, 1.0f};

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
			ImGui::Checkbox("Light", &light1.Enable);
			ImGui::SetCursorPos({ 15.0f, 60.0f });
			//ImGui::PushItemWidth(120.0f);
			
			ImGui::ColorEdit4("Color", cl);
			light1.LightColor.x = cl[0];
				light1.LightColor.y = cl[1];
				light1.LightColor.z = cl[2];
				light1.LightColor.w = cl[3];
			//ImGui::PopItemWidth();
			//ImGui::SetCursorPos({ 15.0f, 90.0f });
			//ImGui::PushItemWidth(120.0f);
			ImGui::DragFloat3("Location", loc, 0.1f);
			cube1.SetLocation(glm::vec3(loc[0], loc[1], loc[2]));
			ImGui::DragFloat3("Rotation", rot, 0.1f);
			cube1.SetRotation(glm::vec3(rot[0], rot[1], rot[2]));
			if (ImGui::DragFloat3("Scale", sc, 0.1f)) {
				cube1.SetScale(glm::vec3(sc[0], sc[1], sc[2]));
			};



			if (ImGui::Button("Reload Shaders")) {
				cube1.MeshShader.ReloadShaders();
				cube2.MeshShader.ReloadShaders();
			}
			ImGui::End();

			glUniform3f(glGetUniformLocation(cube1.MeshShader.shaderID, "CamPos"), cam.Position.x, cam.Position.y, cam.Position.z);
			glUniform3f(glGetUniformLocation(cube2.MeshShader.shaderID, "CamPos"), cam.Position.x, cam.Position.y, cam.Position.z);

			//Draw
			cube1.Draw();
			cube2.Draw();
			light1.Draw();

			ui.Draw();

			win.SwapBufers();
		}
	}

};