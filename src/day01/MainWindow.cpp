#include "MainWindow.h"

MainWindow::MainWindow(string title, int xRes, int yRes) {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	m_window = glfwCreateWindow(xRes, yRes, title.c_str(), nullptr, nullptr);
}

void MainWindow::Initialize()
{
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	cout << "Vulkan Extension Count: " << extensionCount << endl;
}

void MainWindow::MainLoop() {
	while (!glfwWindowShouldClose(m_window)) {
		glfwPollEvents();
	}
}

MainWindow::~MainWindow()
{
	glfwDestroyWindow(m_window);

	glfwTerminate();
}
