#pragma once

#include "Core.h"
#include "Console.h"

#include <string>
#include <fstream>

namespace PE
{
	inline std::ofstream log_file;
	inline PE::Console * console;

	void LogInit(PE::Console * a_console);
	void LogDeInit();
	void ENGINE_API LogError(std::string string);
	void ENGINE_API LogWarning(std::string string);
	void ENGINE_API LogInfo(std::string string);
	void ENGINE_API LogGeneric(std::string string);
};
