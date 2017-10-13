#pragma once

#include "Main.h"

#include "main_window.h"
#include "vulkan_renderer.h"
#include "logger.h"
#include "config_parser.h"

class main_wrapper
{
public:
	main_wrapper()
	{
		m_log_ = new logger(FILENAME_LOG);
		m_config_ = new config_parser(FILENAME_CONFIG);
		m_vulkan_renderer_ = new vulkan_renderer(m_log_);

		m_window_ = new main_window(APP_NAME, m_config_->get_int(CONFIG_XRES), m_config_->get_int(CONFIG_YRES), m_log_);
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