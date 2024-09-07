#include "Window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Window::Open() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(width, height, "Moty's Engine", NULL, NULL);
	if (!window) {
		glfwTerminate();
		Error err(001, "Failed to create GLFW window");
		throw (err);
		
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetWindowAspectRatio(window, 16, 9);
	std::cout << "GLFW window create!\n";
	loadGL();
	glViewport(0, 0, width, height);
}

void Window::Close()
{
	glfwSetWindowShouldClose(window, 1);
}

void Window::SwapBufers()
{
	glfwSwapBuffers(window);
	glfwPollEvents();

}

bool Window::WindowShouldClose()
{
	return glfwWindowShouldClose(window);
}

int Window::GetKeyValue(int key)
{
	std::cout << glfwGetKey(window, GLFW_KEY_ESCAPE);
	return glfwGetKey(window, key);
}

int Window::getWindowWidth()
{
	glfwGetWindowSize(window, &width, &height);
	return width;
}

int Window::getWindowHeight()
{
	glfwGetWindowSize(window, &width, &height);
	return height;
}

void Window::setWindowSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

GLFWwindow* Window::getWindowRef()
{
	return window;
}

void Window::SetTitle(std::string title)
{
	glfwSetWindowTitle(window, title.c_str());
}

Window::~Window()
{
	std::cout << "Closing window..\n";
}
