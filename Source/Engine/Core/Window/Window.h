#pragma once

#include "../RHI/OpenGL/loadGL.cpp"

#include "GLFW/glfw3.h"
#include "iostream"

#include "Error.h"

class Window
{
public:
	void Open();
	void Close();
	void SwapBufers();
	bool WindowShouldClose();
	int GetKeyValue(int key);

	int getWindowWidth();
	int getWindowHeight();
	void setWindowSize(int width, int height);

	GLFWwindow* getWindowRef();

	void SetTitle(std::string title);


	~Window();

private:
	GLFWwindow* window;
	int width = 1024, height = 576;
};

