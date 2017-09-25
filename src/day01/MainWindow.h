#pragma once

#include "Main.h"

class MainWindow {
public:
	MainWindow(string title, int xRes, int yRes);

	void Initialize();

	void MainLoop();

	~MainWindow();
private:
	GLFWwindow * m_window;
};
