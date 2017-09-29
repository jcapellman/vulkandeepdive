#include "main.h"

#include "MainWindow.h"
#include "VulkanRenderer.h"

int main()
{
	VulkanRenderer vRenderer;
	MainWindow mWindow("Vulkan Deep-dive Day 01", 720, 480);
	
	mWindow.Initialize(vRenderer);

	mWindow.MainLoop();

	return 0;
}
