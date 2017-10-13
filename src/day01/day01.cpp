#include "main_wrapper.h"

int main()
{
	auto m_window = main_wrapper();

	auto init_result = m_window.init();

	if (!init_result)
	{
		return 0;
	}

	m_window.run();

	return 0;
}
