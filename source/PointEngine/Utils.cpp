#include "Utils.h"

#include <cmath>

using namespace PE::Utils;

void Timer::Reset()
{
	begin_time = std::chrono::high_resolution_clock::now();
}

Color::Color()
{
	this->r = 255;
	this->g = 255;
	this->b = 255;
	this->a = 255;

}

Color::Color(uint8_t r, uint8_t g, uint8_t b)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 255;
}


Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

std::chrono::duration<float> Timer::GetTime()
{
	return (std::chrono::high_resolution_clock::now() - begin_time);
}

bool Timer::HasTimeElapsed(float time)
{
	if ( GetTime().count() >= time)
	{
		return true;
	}

	return false;
}

int Timer::TimesTimeElapsed(float time)
{
	return std::floor(GetTime().count() / time);
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

bool PE::Utils::StringToBool(std::string str)
{
	if (str == "true" || str == "1")
		return true;
	else if (str == "false" || str == "0")
		return false;
	else
		return false;
}

float PE::Utils::DegToRads(float degrees)
{
	return degrees * 0.01745329251;
}
