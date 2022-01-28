#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace corvus {
	class CorvusWindow {
	public:
		CorvusWindow(int w, int h, std::string name);
		~CorvusWindow();

		CorvusWindow(const CorvusWindow&) = delete;
		CorvusWindow& operator=(const CorvusWindow&) = delete;

		bool shouldClose() { return glfwWindowShouldClose(window); }

		void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

	private:
		void initWindow();

		const int width;
		const int height;

		std::string windowName;
		GLFWwindow* window;
	};
}	//namespace corvus