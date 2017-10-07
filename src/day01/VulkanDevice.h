#pragma once

#include "Main.h"

class vulkan_device
{
	public:
		string get_name() const
		{
			return string(m_physical_device_properties_.deviceName);
		}

		explicit vulkan_device(const VkPhysicalDevice physical_device): m_device_(nullptr)
		{
			m_physical_device_ = physical_device;

			memset(&m_physical_device_properties_, 0, sizeof m_physical_device_properties_);
			vkGetPhysicalDeviceProperties(m_physical_device_, &m_physical_device_properties_);
		}
	private:
		VkPhysicalDevice m_physical_device_;

		VkDevice m_device_;

		VkPhysicalDeviceProperties m_physical_device_properties_;
};
