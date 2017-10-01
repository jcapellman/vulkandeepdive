#pragma once

#include "Main.h"
#include "ReturnSet.h"
#include "BaseManager.h"

class IRenderer : public BaseManager
{
public:
	explicit IRenderer(Logger * logger) : BaseManager(logger) {}

	virtual ~IRenderer() = default;
	virtual string GetName() = 0;
	virtual ReturnSet<bool> Initialize() = 0;
	virtual void Render() = 0;
};
