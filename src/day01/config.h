#pragma once

#include "Main.h"

class config
{
	public:
		explicit config(string file_name)
		{
			string line;
			string buffer;

			ifstream config_file(file_name);

			if (config_file.is_open())
			{
				while (getline(config_file, line))
				{
					stringstream ss(buffer);

					string key;
					string value;
					auto key_set = false;

					while (ss >> buffer)
					{
						if (key_set)
						{
							value = buffer;
						} else
						{
							key = buffer;
						}
					}

					m_config_values_.insert_or_assign(key, value);
				}

				config_file.close();
			}
		}
	private:
		map<string, string> m_config_values_;
};
