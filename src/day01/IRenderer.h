#pragma once

#include "Main.h"

class IRenderer
{
public:
	virtual ~IRenderer() = default;
	virtual string GetName() = 0;
	virtual bool Initialize() = 0;
	virtual void Render() = 0;
};
