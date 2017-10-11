#pragma once

#include "Main.h"
#include "return_set.h"

class config_parser
{
	public:
		~config_parser()
		{
			m_config_values_.clear();
		}

		explicit config_parser(const string file_name)
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
							key_set = true;
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

		return_set<int> get_int(const string key)
		{
			auto result = get_value(key);

			if (result.has_error())
			{
				return return_set<int>(result.caught_exception());
			}

			return return_set<int>(atoi(result.return_value.c_str()));
		}

		return_set<string> get_string(const string key)
		{
			auto result = get_value(key);

			if (result.has_error())
			{
				return return_set<string>(result.caught_exception());
			}

			return return_set<string>(result.return_value);
		}

		return_set<double> get_double(const string key)
		{
			auto result = get_value(key);

			if (result.has_error())
			{
				return return_set<double>(result.caught_exception());
			}

			return return_set<double>(atof(result.return_value.c_str()));
		}
	private:
		map<string, string> m_config_values_;

		return_set<string> get_value(const string key)
		{
			if (m_config_values_.find(key) == m_config_values_.end())
			{
				return return_set<string>(exception("not found"));
			}

			return return_set<string>(m_config_values_.at(key));
		}
};
