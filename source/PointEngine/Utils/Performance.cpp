#include "Performace.h"

namespace PE
{
	namespace Performance
	{
		void PerformanceProfiler::Begin(std::string tag)
		{
			current_tag = tag;
			timer.Reset();
		}

		void PerformanceProfiler::End()
		{
			timings.insert({ timer.GetTime().count(), current_tag });
			current_tag = "";
		}

		std::map<double, std::string> PerformanceProfiler::GetTimings()
		{
			return timings;
		}

		void PerformanceProfiler::Clear()
		{
			timings.clear();
		}
	}
}