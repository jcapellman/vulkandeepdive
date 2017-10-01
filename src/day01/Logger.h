#pragma once

#include "Main.h"

class Logger
{
public:
	Logger(string filename)
	{
		m_file.open(filename);
	}

	~Logger()
	{
		m_file.close();
	}

	void Add(string message)
	{
		m_file << message << endl;
	}
private:
	ofstream m_file;
};