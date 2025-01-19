#pragma once

#include "corvus_window.hpp"
#include "corvus_pipeline.hpp"
#include "corvus_device.hpp"
#include "corvus_swap_chain.hpp"

#include <memory>
#include <vector>

namespace corvus {
	class FirstApp {
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		FirstApp();
		~FirstApp();

		FirstApp(const FirstApp&) = delete;
		FirstApp& operator=(const FirstApp&) = delete;

		void run();

	private:
		void createPipelineLayout();
		void createPipeline();
		void createCommandBuffers();
		void drawFrame();

		CorvusWindow corvusWindow{ WIDTH, HEIGHT, "Hello Vulkan!" };
		CorvusDevice corvusDevice{ corvusWindow };
		CorvusSwapChain corvusSwapChain{ corvusDevice, corvusWindow.getExtent() };
		std::unique_ptr<CorvusPipeline> corvusPipeline;
		VkPipelineLayout pipelineLayout;
		std::vector<VkCommandBuffer> commandBuffers;
	};
}