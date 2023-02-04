#include "Utils.h"

void PE::Utils::Timer::Reset()
{
	begin_time = std::chrono::high_resolution_clock::now();
}

std::chrono::duration<float> PE::Utils::Timer::GetTime()
{
	return (std::chrono::high_resolution_clock::now() - begin_time);
}
