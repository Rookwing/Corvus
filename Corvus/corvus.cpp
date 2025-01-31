#include"corvus.hpp"

//std
#include<iostream>
#include<stdexcept>

namespace corvus {
	Corvus::Corvus()
	{
	}
	Corvus::~Corvus()
	{
	}
	void Corvus::run() {

		while (!corvusWindow.shouldClose()) {
			glfwPollEvents();
			drawFrame();
		}
	}


	void Corvus::initVulkan() {
		Corvus::createPipelineLayout();
		Corvus::createPipeline();
	}

	void Corvus::cleanup() {
		Corvus::destroyPipelineLayout();
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
			std::cout << "Pipeline Layout Created!" << std::endl;
		}
	}

	void Corvus::destroyPipelineLayout() {
		vkDestroyPipelineLayout(corvusDevice.device(), pipelineLayout, nullptr);
	}

	void Corvus::createPipeline() {
		auto pipelineConfig = CorvusPipeline::defaultPipelineConfigInfo(corvusSwapChain.width(), corvusSwapChain.height());
		pipelineConfig.renderPass = corvusSwapChain.getRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;
		CorvusPipeline::CorvusPipeline(corvusDevice, vertShaderPath, fragShaderPath, pipelineConfig);
	}

	void Corvus::drawFrame() {

	}
}