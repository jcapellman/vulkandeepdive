#pragma once
#include "Main.h"
#include "IRenderer.h"

class VulkanRenderer : IRenderer {
public:
	void Render();

	string GetName()
	{
		return "Vulkan";
	}
private:
	VkInstance instance;
};
