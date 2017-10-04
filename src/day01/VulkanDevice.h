#pragma once

#include "Main.h"

class VulkanDevice
{
	public:
		string GetName() const
		{
			VkPhysicalDeviceProperties deviceProperties;

			memset(&deviceProperties, 0, sizeof deviceProperties);
			vkGetPhysicalDeviceProperties(m_device, &deviceProperties);

			return string(deviceProperties.deviceName);
		}

		explicit VulkanDevice(VkPhysicalDevice device)
		{
			m_device = device;
		}
	private:
		VkPhysicalDevice m_device;
};
