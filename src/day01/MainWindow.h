#pragma once

#include "Main.h"
#include "IRenderer.h"
#include "ReturnSet.h"
#include "Logger.h"
#include "BaseManager.h"

class MainWindow : public BaseManager {
public:
	MainWindow(string title, int xRes, int yRes, Logger * logger);

	ReturnSet<bool> Initialize(IRenderer * renderer);

	void MainLoop() const;

	~MainWindow();
private:
	GLFWwindow * m_window;
	IRenderer * m_renderer;
};
