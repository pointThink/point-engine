#pragma once

#include <PointEngine.h>

using namespace PE;

class Bullet : public Entity::EntityBase
{
	void Init();
	void Draw();
	void Update();
	void Tick();
};

void CreateBullet(Vector pos, double speed, double direction);