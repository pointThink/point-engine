#include "RNG.h"

#include <ctime>
#include <random>

using namespace PE::Random;

RNG::RNG()
{
	seed = time(NULL);
	SetSeed(seed);
}

void RNG::SetSeed(time_t seed)
{
	srand(seed);
}


int RNG::RandomNumber(int min, int max)
{
	return (rand() % max) + min;
}