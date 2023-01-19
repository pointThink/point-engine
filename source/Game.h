#pragma once

#include "Core.h"
#include "Logging.h"
#include "Window.h"

class ENGINE_API Game
{
	public:
	Logger * logger;

	virtual void Run() final;
	
	virtual void Update() final;
	virtual void Draw() final;

	private:
	std::string game_name;
	std::string game_version;
};