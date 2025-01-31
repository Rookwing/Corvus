#pragma once

#include "corvus_window.hpp"
#include "corvus_pipeline.hpp"
#include "corvus_device.hpp"
#include "corvus_swap_chain.hpp"

#include <memory>
#include <vector>

namespace corvus {
	class Corvus {
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		Corvus();
		~Corvus();

		Corvus(const Corvus&) = delete;
		Corvus& operator=(const Corvus&) = delete;

		void run();

	private:
		void createPipelineLayout();
		void createPipeline();
		void createCommandBuffers();
		void drawFrame();
		void destroyPipelineLayout();

		CorvusWindow corvusWindow{ WIDTH, HEIGHT, "Hello Vulkan!" };
		CorvusDevice corvusDevice{ corvusWindow };
		CorvusSwapChain corvusSwapChain{ corvusDevice, corvusWindow.getExtent() };
		std::unique_ptr<CorvusPipeline> corvusPipeline;
		VkPipelineLayout pipelineLayout;
		std::vector<VkCommandBuffer> commandBuffers;
	};
}