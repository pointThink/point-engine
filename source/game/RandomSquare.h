#pragma once

#include <PointEngine.h>

using namespace PE;

class RandomSquare : public Entity::EntityBase
{
	Utils::Color color;

	void Init();

	void Update();
	void Draw();

	void OnCollision(Entity::EntityBase* entity);
};

