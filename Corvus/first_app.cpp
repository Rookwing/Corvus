#include"first_app.hpp"

//std
#include<stdexcept>

namespace corvus {
	FirstApp::FirstApp()
	{
	}
	FirstApp::~FirstApp()
	{
	}
	void FirstApp::run() {
		while (!corvusWindow.shouldClose()) {
			glfwPollEvents();
		}
	}

	void FirstApp::createPipelineLayout() {
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr;

		if (vkCreatePipelineLayout(corvusDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create pipeline layout.");
		}
	}

	void FirstApp::createPipeline() {
		auto pipelineConfig = CorvusPipeline::defaultPipelineConfigInfo(corvusSwapChain.width(), corvusSwapChain.height());
		pipelineConfig.renderPass = corvusSwapChain.getRenderPass();
	}
}