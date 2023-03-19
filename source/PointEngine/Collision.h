#pragma once

#include "Core.h"
#include "Vector.h"

namespace PE
{
	namespace Collision
	{
		class ENGINE_API CollisionBox
		{
			public:
			// indidcates the top right position of circle
			Vector pos;
			Vector size;

			bool CollidesWith(CollisionBox box);
		};

		class ENGINE_API CollisionBall
		{
			public:
			// indicates center of circle
			Vector pos;
			float radius;

			bool CollidesWith(CollisionBall ball);
		};
	}
}
