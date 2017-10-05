#pragma once

#include "Main.h"
#include "IRenderer.h"
#include "ReturnSet.h"
#include "Logger.h"
#include "VulkanDevice.h"

class VulkanRenderer : public IRenderer {
public:
	explicit VulkanRenderer(Logger * logger) : IRenderer(logger), m_instance(nullptr)
	{
	}

	~VulkanRenderer()
	{
		vkDestroyInstance(m_instance, nullptr);

		m_instance = nullptr;
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
	vector<VulkanDevice> m_devices;
};
