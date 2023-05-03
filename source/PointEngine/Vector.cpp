#include "Vector.h"

#include <cmath>
#define PI 3.14159265358979323846

namespace PE
{
	double Vector::GetDistanceTo(Vector vec)
	{
		Vector new_vec;

		new_vec.x = fabs(x - vec.x);
		new_vec.y = fabs(y - vec.y);

		return sqrt(pow(new_vec.x, 2) + pow(new_vec.y, 2));
	}

	double Vector::GetRotationTo(Vector vec)
	{
		Vector direction_vec = vec - *this;
		direction_vec.x = -direction_vec.x;
		direction_vec.y = -direction_vec.y;

		double direction = atan2(direction_vec.y, direction_vec.x) * 57.2957795;

		return direction;
	}

	Vector Vector::operator+(Vector vec2)
	{
		Vector new_vec;

		new_vec.x = x + vec2.x;
		new_vec.y = y + vec2.y;

		return new_vec;
	}

	Vector Vector::operator-(Vector vec2)
	{
		Vector new_vec;

		new_vec.x = x - vec2.x;
		new_vec.y = y - vec2.y;

		return new_vec;
	}
}
