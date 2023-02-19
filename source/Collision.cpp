#include "Collision.h"

#include <iostream>

bool PE::Collision::CollisionBox::CollidesWith(CollisionBox box)
{
	if ( (pos.x >= box.pos.x && pos.x <= box.pos.x + box.size.x) && (pos.y >= box.pos.y && pos.y <= box.pos.y + box.size.y) )
	{
		return true;
	}

	return false;
}

bool PE::Collision::CollisionBall::CollidesWith(CollisionBall ball)
{
	std::cout << pos.GetDistanceTo(ball.pos) << std::endl;

	if (pos.GetDistanceTo(ball.pos) <= (radius + ball.radius))
		return true;

	return false;
}