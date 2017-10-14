#pragma once

#include "config_parser.h"
#include "IRenderer.h"
#include "Logger.h"

struct manager_container
{
	config_parser * config;
	IRenderer * renderer;
	logger * log;
};
