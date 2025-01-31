#include "corvus_window.hpp"

#include <stdexcept>
#include <iostream>

namespace corvus {
	CorvusWindow::CorvusWindow(int w, int h, std::string name) : width{ w }, height{ h }, windowName{ name } {
		initWindow();
	}

	CorvusWindow::~CorvusWindow() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void CorvusWindow::initWindow() {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
	}

	void CorvusWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
	{
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create windows surface");
		}
		else
		{
			std::cout << "Window Surface Created!" << std::endl;
		}
	}
}