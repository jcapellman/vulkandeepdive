#include "VulkanRenderer.h"

void VulkanRenderer::Render() {

}

bool VulkanRenderer::Initialize()
{
	// TODO Properly Initialize Vulkan in Day 2
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	cout << "Vulkan Extension Count: " << extensionCount << endl;

	return true;
}
