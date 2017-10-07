#pragma once
#include "Logger.h"

class base_manager
{
	public:
		explicit base_manager(logger * logger)
		{
			m_logger_ = logger;
		}

		void add_log_message(const string message) const
		{
			m_logger_->add(message);
		}
	private:
		logger * m_logger_;
};
