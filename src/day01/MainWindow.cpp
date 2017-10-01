#include "MainWindow.h"

MainWindow::MainWindow(string title, int xRes, int yRes) {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	m_window = glfwCreateWindow(xRes, yRes, title.c_str(), nullptr, nullptr);
}

bool MainWindow::Initialize(IRenderer * renderer)
{
	m_renderer = renderer;
	
	cout << "Initialzing Graphics Renderer: " << m_renderer->GetName() << endl;

	if (!m_renderer->Initialize()) {
		cout << m_renderer->GetName() << " could not initialize" << endl;

		return false;
	}

	return true;
}

void MainWindow::MainLoop() {
	while (!glfwWindowShouldClose(m_window)) {
		m_renderer->Render();

		glfwPollEvents();
	}
}

MainWindow::~MainWindow()
{
	glfwDestroyWindow(m_window);

	glfwTerminate();
}
