#include "MainWindow.h"

main_window::main_window(string title, const int x_res, const int y_res, logger * logger) : base_manager(logger), m_renderer_(nullptr)
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	m_window_ = glfwCreateWindow(x_res, y_res, title.c_str(), nullptr, nullptr);
}

return_set<bool> main_window::initialize(IRenderer * renderer)
{
	m_renderer_ = renderer;
	
	add_log_message("Initialzing Graphics Renderer: " + m_renderer_->GetName());
	
	auto graphicsRendererInitResult = m_renderer_->Initialize();
	
	if (graphicsRendererInitResult.has_error()) {
		add_log_message(m_renderer_->GetName() + " could not initialize due to an error");

		return return_set<bool>(graphicsRendererInitResult.caught_exception());
	}

	add_log_message(m_renderer_->GetName() + " initialized successfully");

	return return_set<bool>(true);
}

void main_window::main_loop() const
{
	while (!glfwWindowShouldClose(m_window_)) {
		m_renderer_->Render();

		glfwPollEvents();
	}
}

main_window::~main_window()
{
	glfwDestroyWindow(m_window_);

	glfwTerminate();
}
