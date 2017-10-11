#pragma once

#include "Main.h"
#include "IRenderer.h"
#include "return_set.h"
#include "Logger.h"
#include "base_manager.h"

class main_window : public base_manager {
	public:
		main_window(string title, int x_res, int y_res, logger * logger);

		return_set<bool> initialize(IRenderer * renderer);

		void main_loop() const;

		~main_window();
	private:
		GLFWwindow * m_window_;
		IRenderer * m_renderer_;
};