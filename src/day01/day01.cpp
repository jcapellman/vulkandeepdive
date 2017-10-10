#include "main.h"

#include "main_window.h"
#include "vulkan_renderer.h"
#include "logger.h"

int main()
{
	auto * log = new logger(LOG_FILENAME);
	auto * v_renderer = new vulkan_renderer(log);
	main_window m_window(APP_NAME, 720, 480, log);
	
	auto init_result = m_window.initialize(v_renderer);
	
	if (init_result.has_error()) {
		log->add("Could not Initialize (due to " + init_result.exception_string() + "), exiting...");

		return 0;
	}

	m_window.main_loop();

	return 0;
}
