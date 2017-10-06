#pragma once

#include "Main.h"

class VulkanDevice
{
	public:
		string GetName() const
		{
			return string(m_physicalDeviceProperties.deviceName);
		}

		explicit VulkanDevice(VkPhysicalDevice physical_device): m_device(nullptr)
		{
			m_physicalDevice = physical_device;

			memset(&m_physicalDeviceProperties, 0, sizeof m_physicalDeviceProperties);
			vkGetPhysicalDeviceProperties(m_physicalDevice, &m_physicalDeviceProperties);
		}
private:
		VkPhysicalDevice m_physicalDevice;

		VkDevice m_device;

		VkPhysicalDeviceProperties m_physicalDeviceProperties;
};
