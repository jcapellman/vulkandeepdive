#pragma once
#include "Logger.h"

class BaseManager
{
	public:
		explicit BaseManager(Logger * logger)
		{
			m_logger = logger;
		}

		void AddLogMessage(string message) const
		{
			m_logger->Add(message);
		}
	private:
		Logger * m_logger;
};
