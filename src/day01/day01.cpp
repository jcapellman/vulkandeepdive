#include "main.h"

#include "MainWindow.h"

int main()
{
	MainWindow mWindow("Vulkan Deep-dive Day 01", 720, 480);

	mWindow.Initialize();

	mWindow.MainLoop();

	return 0;
}
