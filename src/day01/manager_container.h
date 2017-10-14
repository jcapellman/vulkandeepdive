#pragma once

#include "config_parser.h"
#include "Logger.h"

struct manager_container
{
	config_parser * config;
	logger * log;
};
