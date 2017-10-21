#pragma once

#include "Main.h"

class vulkan_device
{
public:
	string get_name() const
	{
		return string(m_physical_device_properties_.deviceName);
	}

	explicit vulkan_device(const VkPhysicalDevice physical_device) : m_device_(nullptr)
	{
		m_physical_device_ = physical_device;

		memset(&m_physical_device_properties_, 0, sizeof m_physical_device_properties_);
		vkGetPhysicalDeviceProperties(m_physical_device_, &m_physical_device_properties_);

		auto extensions = get_extensions();

		cout << "Supported Vulkan Extensions:" << endl;

		for (auto x = 0; x < extensions.size(); x++)
		{
			cout << x + 1 << ". " << extensions.at(x) << endl;
		}
	}
private:
	VkPhysicalDevice m_physical_device_;

	VkDevice m_device_;

	VkPhysicalDeviceProperties m_physical_device_properties_;

	static vector<string> get_extensions()
	{
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
		vector<string> extension_names;

		for (const auto& extension : extensions) {
			extension_names.push_back(extension.extensionName);
		}

		return extension_names;
	}
};
