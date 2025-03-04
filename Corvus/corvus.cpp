#include"corvus.hpp"

//std
#include<iostream>
#include<stdexcept>

namespace corvus {
	Corvus::Corvus()
	{
		init();
	}
	Corvus::~Corvus()
	{
		cleanup();
	}

	void Corvus::init() {
		createPipelineLayout();
		createPipeline();
		createCommandBuffer();
	}

	void Corvus::run() {

		while (!corvusWindow.shouldClose()) {
			glfwPollEvents();
			drawFrame();
		}
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
		PipelineConfigInfo pipelineConfig{};
		CorvusPipeline::defaultPipelineConfigInfo(pipelineConfig, corvusSwapChain.width(), corvusSwapChain.height());
		pipelineConfig.renderPass = corvusSwapChain.getRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;
		corvusPipeline = std::make_unique<CorvusPipeline>(corvusDevice, vertShaderPath, fragShaderPath, pipelineConfig);
	}

	void Corvus::drawFrame() {
		uint32_t imageIndex;
		auto result = corvusSwapChain.acquireNextImage(&imageIndex);

		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
			throw std::runtime_error("failed to acquire swap chain image");
		}

		result = corvusSwapChain.submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
		if (result != VK_SUCCESS) {
			throw std::runtime_error("failed to present swap chain image");
		}
	}

	void Corvus::createCommandBuffer(){
		commandBuffers.resize(corvusSwapChain.imageCount());

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = corvusDevice.getCommandPool();
		allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

		if (vkAllocateCommandBuffers(corvusDevice.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate command buffers");
		}

		for (int i = 0; i < commandBuffers.size(); i++)
		{
			VkCommandBufferBeginInfo beginInfo{};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

			if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
				throw std::runtime_error("failed to begin recording command buffers");
			}

			VkRenderPassBeginInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
			renderPassInfo.renderPass = corvusSwapChain.getRenderPass();
			renderPassInfo.framebuffer = corvusSwapChain.getFrameBuffer(i);
			
			renderPassInfo.renderArea.offset = { 0, 0 };
			renderPassInfo.renderArea.extent = corvusSwapChain.getSwapChainExtent();

			std::array<VkClearValue, 2> clearValues{};
			clearValues[0].color = { 0.1f, 0.1f, 0.1f, 1.0f };
			clearValues[1].depthStencil = { 1.0f, 0 };
			renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
			renderPassInfo.pClearValues = clearValues.data();

			vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			corvusPipeline->bind(commandBuffers[i]);
			vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

			vkCmdEndRenderPass(commandBuffers[i]);
			if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
				throw std::runtime_error("failed to record command buffer");
			}
		}

	}
}