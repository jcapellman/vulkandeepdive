#pragma once

#include "Main.h"
#include "ReturnSet.h"

class IRenderer
{
public:
	virtual ~IRenderer() = default;
	virtual string GetName() = 0;
	virtual ReturnSet<bool> Initialize() = 0;
	virtual void Render() = 0;
};
