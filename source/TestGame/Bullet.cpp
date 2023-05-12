#include "Bullet.h"

#include <cmath>


void Bullet::Init()
{
	entityName = "bullet";

	layer = -1;

	colidable = true;

	collisionGroup.maxCheckDistance = 50;

	Collision::CollisionBox* cb = new Collision::CollisionBox;

	cb->pos = position;
	cb->size = { 5, 5 };

	collisionGroup.AddObject("collider", cb);

}

void Bullet::Update()
{
	for (Collision::CollisionObject* co : collisionGroup.objects)
	{
		if (co->tag == "collider")
		{
			co->pos = position;
		}
	}

	// check if is out of bounds
	/*
	if (position.x > PE_GAME->window->GetWidth() + PE_GAME->window->camera_offset.x || position.x + PE_GAME->window->camera_offset.x < 0)
		if (position.y > PE_GAME->window->GetHeight() + PE_GAME->window->camera_offset.y || position.y + PE_GAME->window->camera_offset.y < 0)
			PE_GAME->entityManager->RemoveEntity(this);
	*/
}

void Bullet::Tick()
{
	motion.y += 1000 / PE_GAME->ticksPerSecond;
}

void Bullet::Draw()
{
	//PE_GAME->window->DrawSquare(position, { 5, 5 }, { 0, 255, 255, 255 });
	PE_GAME->renderer->DrawQuad(position, { 5, 5 }, { 0, 255, 255, 255 });
}

void CreateBullet(Vector pos, double speed, double direction)
{ 
	Bullet* bullet = new Bullet;

	bullet->position = pos;

	Vector motion;

	motion.x = -speed * std::sin(Utils::DegToRads(direction));
	motion.y = speed * std::cos(Utils::DegToRads(direction));
	
	bullet->motion = motion;

	PE_GAME_STATE->entityManager->AddEntity(bullet);
}
