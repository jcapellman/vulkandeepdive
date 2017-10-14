#include "main_window.h"

main_window::main_window(string title, manager_container container) : base_manager(container), m_renderer_(nullptr)
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	auto xres = DEFAULT_CONFIG_XRES;
	auto yres = DEFAULT_CONFIG_YRES;

	auto config_xres = get_config()->get_int(CONFIG_XRES);

	if (!config_xres.has_error())
	{
		xres = config_xres.return_value;
	}

	auto config_yres = get_config()->get_int(CONFIG_YRES);

	if (!config_yres.has_error())
	{
		yres = config_yres.return_value;
	}

	m_window_ = glfwCreateWindow(xres, yres, title.c_str(), nullptr, nullptr);
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
