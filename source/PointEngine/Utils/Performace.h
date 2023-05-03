#pragma once

#include "Core.h"
#include "Utils.h"

#include <map>

namespace PE
{
	namespace Performance
	{
		class ENGINE_API PerformanceProfiler
		{
			private:
			Utils::Timer timer;
			std::string current_tag;

			std::map<double, std::string> timings;

			public:
			void Begin(std::string tag);
			void End();

			std::map<double, std::string> GetTimings();

			void Clear();
		};
	}
}
