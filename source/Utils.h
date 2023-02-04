/* Collection of small utilites used across the engine */

#pragma once

#include <chrono>

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
	}
};
