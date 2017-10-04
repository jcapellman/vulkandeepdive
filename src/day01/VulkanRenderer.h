#pragma once

#include "Main.h"
#include "IRenderer.h"
#include "ReturnSet.h"
#include "Logger.h"
#include "VulkanDevice.h"

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

	ReturnSet<bool> EnumerateDevices();
private:
	VkInstance m_instance;
	VulkanDevice * m_device;
};
