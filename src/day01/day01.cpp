#include "main.h"

#include "MainWindow.h"
#include "VulkanRenderer.h"
#include "Logger.h"

int main()
{
	auto * logger = new Logger("log.txt");
	auto * vRenderer = new VulkanRenderer(logger);
	MainWindow mWindow("Vulkan Deep-dive Day 01", 720, 480, logger);
	
	auto initResult = mWindow.Initialize(vRenderer);
	
	if (initResult.HasError()) {
		logger->Add("Could not Initialize (due to " + initResult.ExceptionString() + "), exiting...");

		return 0;
	}

	mWindow.MainLoop();

	return 0;
}
