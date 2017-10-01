#include "main.h"

#include "MainWindow.h"
#include "VulkanRenderer.h"

int main()
{
	VulkanRenderer * vRenderer = new VulkanRenderer();
	MainWindow mWindow("Vulkan Deep-dive Day 01", 720, 480);
	
	if (!mWindow.Initialize(vRenderer)) {
		cout << "Could not Initialize, exiting..." << endl;

		return 0;
	}

	mWindow.MainLoop();

	return 0;
}
