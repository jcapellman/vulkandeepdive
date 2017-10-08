#pragma once

#include "Main.h"
#include "return_set.h"
#include "base_manager.h"

class IRenderer : public base_manager
{
	public:
		explicit IRenderer(logger * logger) : base_manager(logger) {}

		virtual ~IRenderer() = default;
		virtual string GetName() = 0;
		virtual return_set<bool> Initialize() = 0;
		virtual void Render() = 0;
};
