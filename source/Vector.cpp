#include "Vector.h"

#include <cmath>

double PE::Vector::GetDistanceTo(Vector vec)
{
	Vector new_vec;

	new_vec.x = fabs(x - vec.x);
	new_vec.y = fabs(y - vec.y);

	return sqrt(pow(new_vec.x, 2) + pow(new_vec.y, 2));
}

PE::Vector PE::Vector::operator+(Vector vec2)
{
	Vector new_vec;

	new_vec.x = x + vec2.x;
	new_vec.y = y + vec2.y;

	return new_vec;
}

PE::Vector PE::Vector::operator-(Vector vec2)
{
	Vector new_vec;

	new_vec.x = x - vec2.x;
	new_vec.y = y - vec2.y;
	
	return new_vec;
}