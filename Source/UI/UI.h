#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/ImGuizmo.h"

#include "glm/glm.hpp"

#include "../Engine/Core/Window/Window.h"
#include "../Engine/Core/Camera/Camera.h"

#include "style.h"
#include "colors.h"

class UI {
	static inline Window* winRef;
	static inline Camera* CameraRef;
	static inline glm::mat4* modelRef;
	glm::vec3* TransformRef;
	glm::vec3* RotationRef;
	glm::vec3* ScaleRef;
	float snap[3] = { 1.0f, 1.0f, 1.0f };

	static inline ImGuizmo::OPERATION CurrentGizmoOperation{ ImGuizmo::TRANSLATE };
	static inline ImGuizmo::MODE CurrentGizmoMode{ImGuizmo::WORLD};

	float GridMat[16]
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
public:
	UI( Window* win, Camera* cam);
	~UI();
	void NewFrame();
	void SetGuizmoOpetationMatrix(
		glm::mat4* NewModelRef,
		glm::vec3* Transform,
		glm::vec3* Rotation,
		glm::vec3* Scale);
	void UpdateGuizmo();
	void Draw();

	void testWin();

	bool Enable = true;
};