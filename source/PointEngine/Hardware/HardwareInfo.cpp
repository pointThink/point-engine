#include "Hardware/HardwareInfo.h"

#include <thread>
#include <intrin.h>

//#include <SDL.h>

#include "Game.h"

namespace PE
{
	namespace Hardware
	{
		CPUInfo GetCPUInfo()
		{
			CPUInfo info;

			int cpuInfo[4] = { -1 };
			char CPUBrandString[0x41];

			memset(CPUBrandString, 0, sizeof(CPUBrandString));

			__cpuid(cpuInfo, 0x80000002);
			memcpy(CPUBrandString, cpuInfo, sizeof(cpuInfo));

			__cpuid(cpuInfo, 0x80000003);
			memcpy(CPUBrandString + 16, cpuInfo, sizeof(cpuInfo));

			__cpuid(cpuInfo, 0x80000004);
			memcpy(CPUBrandString + 32, cpuInfo, sizeof(cpuInfo));

			info.name = std::string(CPUBrandString, 41);

			static int corecount = 0;

			if (corecount == 0)
			{
				FILE* fp;
				char var[5] = { 0 };

				fp = _popen("wmic cpu get NumberOfCores", "r");
				while (fgets(var, sizeof(var), fp) != NULL) sscanf(var, "%d", &corecount);
				_pclose(fp);
			}

			info.coreCount = corecount;
			info.threadCount = 0;//SDL_GetCPUCount();			

			return info;
		}

		GPUInfo GetGPUInfo()
		{
			GPUInfo info;

			return info;
		}
	}
}
