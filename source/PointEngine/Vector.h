#pragma once

#include "Core.h"

namespace PE
{
	class ENGINE_API Vector
	{
	public:
		double x, y;

		double GetDistanceTo(Vector vec);
		double GetRotationTo(Vector vec);

		// some vector maths - PT
		Vector operator+(Vector vec);
		Vector operator-(Vector vec);
	};
};

