#pragma once

#include "Main.h"

class IRenderer
{
public:
	virtual ~IRenderer() = default;
	virtual string GetName() = 0;
};
