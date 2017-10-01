#pragma once

#include "Main.h"
#include "IRenderer.h"
#include "ReturnSet.h"

class MainWindow {
public:
	MainWindow(string title, int xRes, int yRes);

	ReturnSet<bool> Initialize(IRenderer * renderer);

	void MainLoop();

	~MainWindow();
private:
	GLFWwindow * m_window;
	IRenderer * m_renderer;
};
