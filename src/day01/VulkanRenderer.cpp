#include "VulkanRenderer.h"

void vulkan_renderer::Render() {

}

return_set<bool> vulkan_renderer::Initialize()
{
	VkApplicationInfo app_info = {};

	app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app_info.pApplicationName = "VulkanDeepDive";
	app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.pEngineName = "VulaknDeepDive";
	app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	app_info.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	create_info.pApplicationInfo = &app_info;

	uint32_t glfw_extension_count = 0;

	const auto glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

	create_info.enabledExtensionCount = glfw_extension_count;
	create_info.ppEnabledExtensionNames = glfw_extensions;
	create_info.enabledLayerCount = 0;

	const auto result = vkCreateInstance(&create_info, nullptr, &m_instance_);

	if (result != VK_SUCCESS)
	{
		return return_set<bool>(exception("Could not initialize Vulkan Device"));
	}

	auto device_enumeration = enumerate_devices();

	if (device_enumeration.has_error())
	{
		return return_set<bool>(device_enumeration.caught_exception());
	}

	return return_set<bool>(true);
}

return_set<bool> vulkan_renderer::enumerate_devices()
{
	uint32_t device_count = 0;
	auto result = vkEnumeratePhysicalDevices(m_instance_, &device_count, nullptr);

	if (result != VK_SUCCESS) {
		return return_set<bool>(exception("Could not enumerate Vulkan Devices"));
	}

	if (device_count == 0) {
		return return_set<bool>(exception("Could not find any Vulkan Devices"));
	}

	vector<VkPhysicalDevice> vulkanDevices(device_count);

	result = vkEnumeratePhysicalDevices(m_instance_, &device_count, &vulkanDevices[0]);

	if (result != VK_SUCCESS || vulkanDevices.size() == 0) {
		return return_set<bool>(exception("Failed to enumerate device"));
	}

	for (auto device : vulkanDevices)
	{
		auto v_device = vulkan_device(device);

		m_devices_.push_back(v_device);

		add_log_message("Vulkan Device (" + v_device.get_name() + ") enumerated successfully");
	}
	
	return return_set<bool>(true);
}
