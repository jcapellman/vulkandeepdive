#pragma once

#include "Main.h"
#include "IRenderer.h"

class MainWindow {
public:
	MainWindow(string title, int xRes, int yRes);

	void Initialize(IRenderer renderer);

	void MainLoop();

	~MainWindow();
private:
	GLFWwindow * m_window;
	IRenderer * m_renderer;
};
