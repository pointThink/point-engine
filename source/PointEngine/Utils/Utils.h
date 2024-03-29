/* Collection of small utilites used across the engine */

#pragma once

#include <chrono>
#include <string>
#include <vector>
#include <cstdint>

#include "Core.h"

#define PI 3.14159265358979323846

template<typename Base, typename T>
inline bool instanceof(const T* ptr)
{
	return dynamic_cast<const Base*>(ptr) != nullptr;
}

namespace PE
{
	namespace Utils
	{
		class ENGINE_API Timer
		{
			public:
			std::chrono::time_point<std::chrono::high_resolution_clock> begin_time;

			std::chrono::duration<float> GetTime();
			bool HasTimeElapsed(float time);

			/* this name might be confusing
			this just gets how many times the time has elapsed */
			int TimesTimeElapsed(float time);

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

		ENGINE_API std::vector<std::string> SplitString(std::string str, std::string delimiter);
		ENGINE_API bool StringToBool(std::string str);

		ENGINE_API float DegToRads(float degrees);
	}
};
