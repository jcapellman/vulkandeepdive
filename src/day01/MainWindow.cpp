#include "MainWindow.h"

MainWindow::MainWindow(string title, int xRes, int yRes) {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	m_window = glfwCreateWindow(xRes, yRes, title.c_str(), nullptr, nullptr);
}

ReturnSet<bool> MainWindow::Initialize(IRenderer * renderer)
{
	m_renderer = renderer;
	
	cout << "Initialzing Graphics Renderer: " << m_renderer->GetName() << endl;

	auto graphicsRendererInitResult = m_renderer->Initialize();
	
	if (graphicsRendererInitResult.HasError()) {
		cout << m_renderer->GetName() << " could not initialize due to an error" << endl;

		return ReturnSet<bool>(graphicsRendererInitResult.Exception());
	}

	return ReturnSet<bool>(true);
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
