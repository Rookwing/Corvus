#include"corvus.hpp"

//std
#include<iostream>
#include<stdexcept>

namespace corvus {
	Corvus::Corvus()
	{
		Corvus::createPipelineLayout();
	}
	Corvus::~Corvus()
	{
		Corvus::destroyPipelineLayout();
	}
	void Corvus::run() {
		while (!corvusWindow.shouldClose()) {
			glfwPollEvents();
			drawFrame();
		}
	}

	void Corvus::createPipelineLayout() {
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr;

		if (vkCreatePipelineLayout(corvusDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create pipeline layout.");
		}
		else
		{
			std::cout << "Graphics Pipeline Created!" << std::endl;
		}
	}

	void Corvus::destroyPipelineLayout() {
		vkDestroyPipelineLayout(corvusDevice.device(), pipelineLayout, nullptr);
	}

	void Corvus::createPipeline() {
		auto pipelineConfig = CorvusPipeline::defaultPipelineConfigInfo(corvusSwapChain.width(), corvusSwapChain.height());
		pipelineConfig.renderPass = corvusSwapChain.getRenderPass();
	}

	void Corvus::drawFrame() {

	}
}