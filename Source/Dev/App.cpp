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
		cube2.SetLocation(glm::vec3(0.0f, -0.6f, 0.0f));
		cube2.SetScale(glm::vec3(10.f, 0.5f, 10.0f));

		cube1.SetCameraRef(&cam);
		cube2.SetCameraRef(&cam);
		
		Light light1;
		light1.CameraRef = &cam;
		light1.SetLocation(glm::vec3(-1.0f, 1.0f, 0.0f));

		cube1.LightsRef = &light1;
		cube2.LightsRef = &light1;

		cube1.SetTexture("wooden_planks/wooden_planks_d.png", "wooden_planks/wooden_planks_r.png");
		cube2.SetTexture("garage_floor/garage_floor_d.png", "garage_floor/garage_floor_r.png");

		const char* textures[4] = { "wooden_planks/wooden_planks_d.png" , "red_brick/red_brick_d.png",
									"metal_plate/metal_plate_d.png", "container_d.png" };
		std::string current_texture = "wooden_planks/wooden_planks_d.png";

		cube1.GetTextureName();

		UI ui(&win, &cam);
		ImGui::LoadStyles();
		ImGui::LoadColors();

		//temporally varies
		float loc[3] = { 0.0f, 0.0f, 0.0f };
		float rot[3] = { 0.0f, 0.0f, 0.0f };
		float sc[3] = { 1.0f, 1.0f, 1.0f };
		float cl[4] = { 1.0f, 1.0f, 1.0f, 1.0f};
		bool selected = false;

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

			ImGui::Begin("Properties",0, ImGuiWindowFlags_NoCollapse);
			ImGui::Checkbox("Light", &light1.Enable);
			
			ImGui::ColorEdit4("Color", cl);
			light1.LightColor.x = cl[0];
				light1.LightColor.y = cl[1];
				light1.LightColor.z = cl[2];
				light1.LightColor.w = cl[3];
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
			if (ImGui::BeginCombo("Texture", current_texture.c_str())) {

				for (int n = 0; n < 3; n++) {
					//cube1.GetTextureName();
					bool selected = (textures[n] == current_texture);
					if (ImGui::Selectable(textures[n], selected)) { 
						current_texture = textures[n]; 
						cube1.SetTexture(current_texture, "wooden_planks/wooden_planks_r.png");
					}
					else{ ImGui::SetItemDefaultFocus(); }
				}
				ImGui::EndCombo();
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