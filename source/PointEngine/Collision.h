#pragma once

#include <vector>
#include <string>

#include "Core.h"
#include "Vector.h"

namespace PE
{
	namespace Collision
	{
		class ENGINE_API CollisionObject
		{
			public:
			Vector pos = { 0, 0 };
			std::string tag = "NULL";

			virtual bool CollidesWith(CollisionObject* object);
		};

		class ENGINE_API CollisionBox : public CollisionObject
		{
			public:
			Vector size = { 0, 0 };

			bool CollidesWith(CollisionObject* object);
		};

		class ENGINE_API CollisionBall : public CollisionObject
		{
			public:
			float radius = 0;
			bool CollidesWith(CollisionObject* object);
		};

		class ENGINE_API CollisionGroup
		{
			public:
			unsigned int maxCheckDistance = 500; // value pulled out of my ass

			std::vector<CollisionObject*> objects;

			bool CollidesWithGroup(CollisionGroup* group);
			bool CollidesWith(CollisionObject* object);

			void AddObject(std::string tag, CollisionObject* object);
			void Clear();

			//void UpdatePos(Vector pos);
		};
	}
}
