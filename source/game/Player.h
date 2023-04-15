#pragma once
#include "Entity/Entity.h"

using namespace PE;

class Player : public Entity::EntityBase
{
	int speed = 100;

	void Init();

	void Draw();
	void Update();
	void Tick();
};

