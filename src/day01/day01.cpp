#include "main.h"

#include "main_window.h"
#include "vulkan_renderer.h"
#include "logger.h"
#include "config_parser.h"

int main()
{
	auto * log = new logger(FILENAME_LOG);
	auto * config = new config_parser(FILENAME_CONFIG);

	auto * v_renderer = new vulkan_renderer(log);
	main_window m_window(APP_NAME, config->get_int(CONFIG_XRES), config->get_int(CONFIG_YRES), log);
	
	auto init_result = m_window.initialize(v_renderer);
	
	if (init_result.has_error()) {
		log->add("Could not Initialize (due to " + init_result.exception_string() + "), exiting...");

		return 0;
	}

	m_window.main_loop();

	return 0;
}
