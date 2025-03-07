#pragma once

#include "corvus_window.hpp"
#include "corvus_pipeline.hpp"
#include "corvus_device.hpp"
#include "corvus_swap_chain.hpp"

#include <memory>
#include <vector>
#include <array>

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
		void init();
		void cleanup();

	private:
		void createPipelineLayout();
		void destroyPipelineLayout();
		void createPipeline();
		void createCommandBuffer();
		void drawFrame();

		std::string vertShaderPath{ "shaders/compiled/simple_shader.vert.spv" };
		std::string fragShaderPath{ "shaders/compiled/simple_shader.frag.spv" };
		CorvusWindow corvusWindow{ WIDTH, HEIGHT, "Hello Vulkan!" };
		CorvusDevice corvusDevice{ corvusWindow };
		CorvusSwapChain corvusSwapChain{ corvusDevice, corvusWindow.getExtent() };
		std::unique_ptr<CorvusPipeline> corvusPipeline;
		VkPipelineLayout pipelineLayout{};
		std::vector<VkCommandBuffer> commandBuffers;
	};
}