#pragma once

#include "Main.h"
#include "IRenderer.h"
#include "ReturnSet.h"
#include "Logger.h"

class VulkanRenderer : public IRenderer {
public:
	VulkanRenderer(Logger * logger) : IRenderer(logger) { }

	~VulkanRenderer()
	{
		vkDestroyInstance(m_instance, nullptr);
	}
	void Render() override;

	string GetName() override
	{
		return "Vulkan";
	}

	ReturnSet<bool> Initialize() override;
private:
	VkInstance m_instance;
};
