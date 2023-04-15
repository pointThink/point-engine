#pragma once

#include "Core.h"

#include <ctime>


namespace PE
{
	namespace Random
	{
		class ENGINE_API RNG
		{
		private:
			time_t seed;

		public:
			RNG();
			void SetSeed(time_t seed);

			int RandomNumber(int min, int max);
		};
	}
}