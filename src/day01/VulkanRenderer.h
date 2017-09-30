#pragma once
#include "Main.h"
#include "IRenderer.h"

class VulkanRenderer : public IRenderer {
public:
	void Render() override;

	string GetName() override
	{
		return "Vulkan";
	}

	bool Initialize() override;
private:
	VkInstance instance;
};
