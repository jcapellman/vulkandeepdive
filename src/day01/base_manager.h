#pragma once

#include "manager_container.h"

class base_manager
{
	public:
		explicit base_manager(manager_container container)
		{
			m_container_ = container;
		}

		void add_log_message(const string message) const
		{
			m_container_.log->add(message);
		}
	private:
		manager_container m_container_;
};
