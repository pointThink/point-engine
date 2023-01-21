#pragma once

#include "Core.h"
#include <string>


namespace PE
{
	void ENGINE_API LogError(std::string string);
	void ENGINE_API LogWarning(std::string string);
	void ENGINE_API LogInfo(std::string string);
	void ENGINE_API LogGeneric(std::string string);
};