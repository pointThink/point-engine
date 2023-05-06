#pragma once

#include "Core.h"

#include <string>

namespace PE
{
	namespace Error
	{
		// Shows a messagebox and exits the game
		void ENGINE_API CriticalError(std::string message);
	}
}