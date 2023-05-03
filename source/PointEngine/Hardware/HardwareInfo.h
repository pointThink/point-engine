#pragma once

#include "Core.h"

#include <string>

namespace PE
{
	namespace Hardware
	{
		class CPUInfo
		{
		public:
			std::string name;

			int coreCount;
			int threadCount;
			float clockSpeed;
		};

		class GPUInfo
		{
		public:
			std::string name;

			float vram;
			float clockSpeed;
		};

		ENGINE_API CPUInfo GetCPUInfo();
		ENGINE_API GPUInfo GetGPUInfo();
	}
}