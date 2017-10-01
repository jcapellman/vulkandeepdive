#pragma once
#include "Main.h"
#include "IRenderer.h"
#include "ReturnSet.h"

class VulkanRenderer : public IRenderer {
public:
	void Render() override;

	string GetName() override
	{
		return "Vulkan";
	}

	ReturnSet<bool> Initialize() override;
private:
	VkInstance instance;
};
