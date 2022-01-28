#pragma once

#include "corvus_window.hpp"
#include "corvus_pipeline.hpp"
#include "corvus_device.hpp"

namespace corvus {
	class FirstApp {
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		void run();

	private:
		CorvusWindow corvusWindow{ WIDTH, HEIGHT, "Hello Vulkan!" };
		CorvusDevice corvusDevice{ corvusWindow };
		CorvusPipeline corvusPipeline{
			corvusDevice,
			"shaders/compiled/simple_shader.vert.spv",
			"shaders/compiled/simple_shader.frag.spv",
			CorvusPipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT) };
	};
}