#include "UI.h"

UI::UI( Window* win, Camera* cam)
{
	winRef = win;
	CameraRef = cam;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(win->getWindowRef(), true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

UI::~UI()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void UI::NewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void UI::Update(){

}

void UI::Draw()
{
	if (CameraRef->MovementActive == false) {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}


void UI::SetGuizmoOpetationMatrix(
	glm::mat4* NewModelRef,
	glm::vec3* Transform,
	glm::vec3* Rotation,
	glm::vec3* Scale)
{
	TransformRef = Transform;
	RotationRef = Rotation;
	ScaleRef = Scale;
	modelRef = NewModelRef;
}

void UI::UpdateGuizmo()
{
	/*if (CameraRef->MovementActive == false) {
		if (ImGui::IsKeyPressed(ImGuiKey_W)) {
			CurrentGizmoOperation = ImGuizmo::TRANSLATE;
		}
		if (ImGui::IsKeyPressed(ImGuiKey_E)) {
			CurrentGizmoOperation = ImGuizmo::ROTATE;
		}
		if (ImGui::IsKeyPressed(ImGuiKey_R)) {
			CurrentGizmoOperation = ImGuizmo::SCALE;
		}
	}*/
}


void UI::testWin()
{
	/*ImGui::SetNextWindowSize({ 250.f,368.f });

	ImGui::Begin("Properties");
	ImGui::SetCursorPos({ 21.f,43.f });
	ImGui::Checkbox("Light", &the_bool);
	ImGui::SetCursorPos({ 31.f,100.f });
	ImGui::PushItemWidth(334.000000);
	ImGui::SliderFloat("sliderF4", &valueF, 0, 100);
	ImGui::PopItemWidth();

	ImGui::End();*/
}
