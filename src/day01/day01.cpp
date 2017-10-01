#include "main.h"

#include "MainWindow.h"
#include "VulkanRenderer.h"

int main()
{
	auto * vRenderer = new VulkanRenderer();
	MainWindow mWindow("Vulkan Deep-dive Day 01", 720, 480);
	
	auto initResult = mWindow.Initialize(vRenderer);
	
	if (initResult.HasError()) {
		cout << "Could not Initialize (due to " << initResult.ExceptionString() << "), exiting..." << endl;

		return 0;
	}

	mWindow.MainLoop();

	return 0;
}
