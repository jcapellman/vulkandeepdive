#pragma once

#include "Main.h"
#include "return_set.h"
#include "base_manager.h"

class igfxrenderer : public base_manager
{
	public:
		explicit igfxrenderer(manager_container container) : base_manager(container) {}

		virtual ~igfxrenderer() = default;
		virtual string GetName() = 0;
		virtual return_set<bool> Initialize() = 0;
		virtual void Render() = 0;
};
