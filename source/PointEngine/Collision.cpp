#include "Collision.h"

#include <iostream>
#include "Utils/Utils.h"

#include "Logging.h"

namespace PE
{
	namespace Collision
	{
		bool CollisionObject::CollidesWith(CollisionObject* object)
		{
			PE::LogWarning("Default CollidesWith called!");
			return false;
		}

		bool CollisionBox::CollidesWith(CollisionObject* object)
		{
			if (instanceof<CollisionBox>(object))
			{
				CollisionBox* box = (CollisionBox*)object;//dynamic_cast<CollisionBox*>(obj_ptr);

				if ((pos.x >= box->pos.x && pos.x <= box->pos.x + box->size.x) && (pos.y >= box->pos.y && pos.y <= box->pos.y + box->size.y))
				{
					return true;
				}

				return false;
			}

			return false;
		}

		bool CollisionBall::CollidesWith(CollisionObject* object)
		{
			if (instanceof<CollisionBall>(object))
			{
				CollisionBall* ball = (CollisionBall*)object;

				std::cout << pos.GetDistanceTo(ball->pos) << std::endl;

				if (pos.GetDistanceTo(ball->pos) <= (radius + ball->radius))
					return true;
			}

			return false;
		}

		void CollisionGroup::AddObject(std::string tag, CollisionObject* object)
		{
			object->tag = tag;
			objects.push_back(object);
		}

		void CollisionGroup::Clear()
		{
			objects.clear();
		}

		bool CollisionGroup::CollidesWithGroup(CollisionGroup* group)
		{
			for (CollisionObject* o : objects)
			{
				for (CollisionObject* o1 : group->objects)
				{
					if (o->CollidesWith(o1))
					{
						//std::cout << o << std::endl;
						//std::cout << o1 << std::endl;

						return true;
					}
				}
			}

			return false;
		}
	}
}