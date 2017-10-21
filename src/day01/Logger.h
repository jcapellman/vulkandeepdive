#pragma once

#include "Main.h"

class logger
{
	public:
		explicit logger(const string filename)
		{
			m_file_.open(filename);
		}

		~logger()
		{
			m_file_.close();
		}

		void add(const string message)
		{
			//m_file_ << message << endl;
		}
	private:
		ofstream m_file_;
};