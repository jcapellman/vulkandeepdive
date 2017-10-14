#pragma once

#include "Main.h"

#include "main_window.h"
#include "vulkan_renderer.h"
#include "logger.h"
#include "config_parser.h"
#include "manager_container.h"

class main_wrapper
{
public:
	main_wrapper()
	{
		m_log_ = new logger(FILENAME_LOG);
		m_config_ = new config_parser(FILENAME_CONFIG);
		m_vulkan_renderer_ = new vulkan_renderer(get_wrapper());

		m_window_ = new main_window(APP_NAME, get_wrapper());
	}

	manager_container get_wrapper()
	{
		auto m_container = manager_container();

		m_container.config = m_config_;
		m_log_ = m_log_;

		return m_container;
	}

	bool init() const
	{
		auto init_result = m_window_->initialize(m_vulkan_renderer_);

		if (init_result.has_error()) {
			m_log_->add("Could not Initialize (due to " + init_result.exception_string() + "), exiting...");

			return false;
		}

		return true;
	}

	void run() const
	{
		m_window_->main_loop();
	}

	~main_wrapper()
	{
		m_log_ = nullptr;
		m_config_ = nullptr;
		m_vulkan_renderer_ = nullptr;
	}
private:
	logger * m_log_;
	config_parser * m_config_;
	vulkan_renderer * m_vulkan_renderer_;
	main_window * m_window_;
};