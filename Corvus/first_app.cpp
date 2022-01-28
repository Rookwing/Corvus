#include"first_app.hpp"

namespace corvus {
	void FirstApp::run() {
		while (!corvusWindow.shouldClose()) {
			glfwPollEvents();
		}
	}
}