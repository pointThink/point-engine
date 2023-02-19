/* Collection of small utilites used across the engine */

#pragma once

#include <chrono>
#include <string>
#include <vector>
#include <cstdint>

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

		class ENGINE_API Color
		{
			public:
			Color();
			Color(uint8_t r, uint8_t g, uint8_t b);
			Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

			uint8_t r, g, b, a;

		};

		std::vector<std::string> SplitString(std::string str, std::string delimiter);
		bool StringToBool(std::string str);
	}
};
