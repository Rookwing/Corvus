#pragma once

#include "corvus_device.hpp"
#include "corvus_swap_chain.hpp"

//std
#include<string>
#include<vector>

namespace corvus {
	struct PipelineConfigInfo {
		PipelineConfigInfo()
			: viewport{}
			, scissor{}
			, viewportInfo{}
			, inputAssemblyInfo{}
			, rasterizationInfo{}
			, multisamplestate{}
			, colorBlendAttachment{}
			, colorBlendInfo{}
			, depthStencilInfo{}
			, pipelineLayout(nullptr)
			, renderPass(nullptr)
			, subpass(0) {
		}

		PipelineConfigInfo(const PipelineConfigInfo&) = delete;
		PipelineConfigInfo& operator=(const PipelineConfigInfo&) = delete;

		VkViewport viewport;
		VkRect2D scissor;
		VkPipelineViewportStateCreateInfo viewportInfo;
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo multisamplestate;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo colorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
		VkPipelineLayout pipelineLayout;
		VkRenderPass renderPass;
		uint32_t subpass;
	};

	class CorvusPipeline {
	public:
		CorvusPipeline(
			CorvusDevice& device,
			const std::string& vertFilepath,
			const std::string& fragFilepath,
			const PipelineConfigInfo& configInfo);
		~CorvusPipeline();

		CorvusPipeline(const CorvusPipeline&) = delete; //want to avoid duplicating pointers
		void operator=(const CorvusPipeline&) = delete;

		void bind(VkCommandBuffer commandBuffer);

		static void defaultPipelineConfigInfo(PipelineConfigInfo& configInfo, uint32_t width, uint32_t height);
	private:
		static std::vector<char> readFile(const std::string& filepath);

		void createGraphicsPipeline(
			const std::string& vertFilepath,
			const std::string& fragFilepath,
			const PipelineConfigInfo& configInfo);

		void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

		CorvusDevice& corvusDevice; //potentionally memory unsafe
		VkPipeline graphicsPipeline;
		VkShaderModule vertShaderModule;
		VkShaderModule fragShaderModule;
		VkPipelineLayout pipelineLayout{};
	};
}