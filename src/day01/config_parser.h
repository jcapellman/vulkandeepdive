#pragma once

#include "Main.h"
#include "return_set.h"

enum CONFIG_OPTIONS {
	CONFIG_XRES,
	CONFIG_YRES,
	CONFIG_GFX_RENDERER
};

// Default Config Keys
#define DEFAULT_CONFIG_XRES "720"
#define DEFAULT_CONFIG_YRES "480"
#define DEFAULT_CONFIG_GFX_RENDERER "Vulkan"

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

					CONFIG_OPTIONS key;
					string value;
					auto key_set = false;

					while (ss >> buffer)
					{
						if (key_set)
						{
							value = buffer;
							key_set = false;
						} else
						{
							// TODO: There has to be a better way to do this part
							if (buffer == "xres") {
								key = CONFIG_XRES;
							}
							else if (buffer == "yres") {
								key = CONFIG_YRES;
							}
							else if (buffer == "gfx_renderer") {
								key = CONFIG_GFX_RENDERER;								
							}

							key_set = true;
						}
					}

					m_config_values_.insert_or_assign(key, value);
				}

				config_file.close();
			}
		}

		return_set<int> get_int(CONFIG_OPTIONS config_option)
		{
			auto result = get_value(config_option);

			if (result.has_error())
			{
				return return_set<int>(result.caught_exception());
			}

			return return_set<int>(atoi(result.return_value.c_str()));
		}

		return_set<string> get_string(CONFIG_OPTIONS config_option)
		{
			auto result = get_value(config_option);

			if (result.has_error())
			{
				return return_set<string>(result.caught_exception());
			}

			return return_set<string>(result.return_value);
		}

		return_set<double> get_double(CONFIG_OPTIONS config_option)
		{
			auto result = get_value(config_option);

			if (result.has_error())
			{
				return return_set<double>(result.caught_exception());
			}

			return return_set<double>(atof(result.return_value.c_str()));
		}
	private:
		map<CONFIG_OPTIONS, string> m_config_values_;

		return_set<string> get_default_value(CONFIG_OPTIONS config_option) {
			switch (config_option) {
				case CONFIG_GFX_RENDERER:					
					return return_set<string>(DEFAULT_CONFIG_GFX_RENDERER);
				case CONFIG_YRES:
					return return_set<string>(DEFAULT_CONFIG_YRES);
				case CONFIG_XRES:
					return return_set<string>(DEFAULT_CONFIG_XRES);
			}

			return return_set<string>(exception("No default value for " + config_option));
		}

		return_set<string> get_value(CONFIG_OPTIONS config_option)
		{
			if (m_config_values_.find(config_option) == m_config_values_.end())
			{
				return get_default_value(config_option);
			}

			return return_set<string>(m_config_values_.at(config_option));
		}
};
