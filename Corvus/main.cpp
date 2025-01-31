#include "corvus.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main() {
	corvus::Corvus app{};

	app.initVulkan();

	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		app.cleanup();

		return EXIT_FAILURE;
	}
	
	app.cleanup();
	return EXIT_SUCCESS;
}