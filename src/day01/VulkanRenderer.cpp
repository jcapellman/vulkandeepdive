#include "VulkanRenderer.h"

void VulkanRenderer::Render() {

}

ReturnSet<bool> VulkanRenderer::Initialize()
{
	VkApplicationInfo appInfo = {};

	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "VulkanDeepDive";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "VulaknDeepDive";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	uint32_t glfwExtensionCount = 0;

	auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;
	createInfo.enabledLayerCount = 0;

	auto result = vkCreateInstance(&createInfo, nullptr, &m_instance);

	if (result != VK_SUCCESS)
	{
		return ReturnSet<bool>(exception("Could not initialize Vulkan Device"));
	}

	auto deviceEnumeration = EnumerateDevices();

	if (deviceEnumeration.HasError())
	{
		return ReturnSet<bool>(deviceEnumeration.Exception());
	}

	return ReturnSet<bool>(true);
}

ReturnSet<bool> VulkanRenderer::EnumerateDevices() const
{
	uint32_t deviceCount = 0;
	auto result = vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);

	if (result != VK_SUCCESS) {
		return ReturnSet<bool>(exception("Could not enumerate Vulkan Devices"));
	}

	if (deviceCount == 0) {
		return ReturnSet<bool>(exception("Could not find any Vulkan Devices"));
	}

	vector<VkPhysicalDevice> vulkanDevices(deviceCount);

	result = vkEnumeratePhysicalDevices(m_instance, &deviceCount, &vulkanDevices[0]);

	if (result != VK_SUCCESS) {
		return ReturnSet<bool>(exception("Failed to enumerate device"));
	}

	EnumerateDeviceInformation();

	return ReturnSet<bool>(true);
}

void VulkanRenderer::EnumerateDeviceInformation() const
{
	VkPhysicalDeviceProperties deviceProperties;
	
	memset(&deviceProperties, 0, sizeof deviceProperties);
	vkGetPhysicalDeviceProperties(m_physical_device, &deviceProperties);

	AddLogMessage("Vulkan Device (" + string(deviceProperties.deviceName) +") enumerated successfully");
}
