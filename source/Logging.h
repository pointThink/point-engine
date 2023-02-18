#pragma once

#include "Core.h"
#include <string>
#include <fstream>

namespace PE
{
	inline std::ofstream log_file;

	void LogInit();
	void LogDeInit();
	void ENGINE_API LogError(std::string string);
	void ENGINE_API LogWarning(std::string string);
	void ENGINE_API LogInfo(std::string string);
	void ENGINE_API LogGeneric(std::string string);
};
