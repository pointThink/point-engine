#include "Utils.h"

void PE::Utils::Timer::Reset()
{
	begin_time = std::chrono::high_resolution_clock::now();
}

std::chrono::duration<float> PE::Utils::Timer::GetTime()
{
	return (std::chrono::high_resolution_clock::now() - begin_time);
}

std::vector<std::string> PE::Utils::SplitString(std::string string, std::string delimiter)
{
	// some random code found on so and slightly modified - PT
	std::vector<std::string> finalized;

	int pos = 0;
	std::string token;

	while ((pos = string.find(delimiter)) != std::string::npos) {
		token = string.substr(0, pos);
		finalized.push_back(token);
		string.erase(0, pos + delimiter.length());
	}

	finalized.push_back(string);

	return finalized;
}
