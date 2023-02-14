/* Collection of small utilites used across the engine */

#pragma once

#include <chrono>
#include <string>
#include <vector>

#include "Core.h"

namespace PE
{
	namespace Utils
	{
		class ENGINE_API Timer
		{
			public:
			std::chrono::time_point<std::chrono::high_resolution_clock> begin_time;

			std::chrono::duration<float> GetTime();
			void Reset();
		};

		std::vector<std::string> SplitString(std::string string, std::string delimiter);
	}
};
