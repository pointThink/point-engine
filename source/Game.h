#pragma once

#include "Core.h"

class ENGINE_API Game
{
	public:
	virtual void Run() final;
	
	virtual void Update() final;
	virtual void Draw() final;
};