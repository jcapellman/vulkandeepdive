#include "main.h"

#include "MainWindow.h"
#include "VulkanRenderer.h"
#include "Logger.h"

int main()
{
	auto * log = new logger("log.txt");
	auto * v_renderer = new vulkan_renderer(log);
	main_window m_window("Vulkan Deep-dive Day 01", 720, 480, log);
	
	auto init_result = m_window.initialize(v_renderer);
	
	if (init_result.has_error()) {
		log->add("Could not Initialize (due to " + init_result.exception_string() + "), exiting...");

		return 0;
	}

	m_window.main_loop();

	return 0;
}
