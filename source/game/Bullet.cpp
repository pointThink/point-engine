#include "Bullet.h"

#include <cmath>

void Bullet::Init()
{
	layer = -1;

	colidable = false;

	collision_group.max_check_distance = 50;

	Collision::CollisionBox* cb = new Collision::CollisionBox;

	cb->pos = position;
	cb->size = { 5, 5 };

	collision_group.AddObject("collider", cb);

}

void Bullet::Update()
{
	for (Collision::CollisionObject* co : collision_group.objects)
	{
		if (co->tag == "collider")
		{
			co->pos = position;
		}
	}

	// check if is out of bounds
	
	if (position.x > PE_GAME->window->GetWidth() + PE_GAME->window->camera_offset.x || position.x + PE_GAME->window->camera_offset.x < 0)
		if (position.y > PE_GAME->window->GetHeight() + PE_GAME->window->camera_offset.y || position.y + PE_GAME->window->camera_offset.y < 0)
			PE_GAME->entity_manager->RemoveEntity(this);
	
}

void Bullet::Tick()
{
	motion.y += 1000 / PE_GAME->ticks_per_second;
}

void Bullet::Draw()
{
	PE_GAME->window->DrawSquare(position, { 5, 5 }, { 0, 255, 255, 255 });
}

void CreateBullet(Vector pos, double speed, double direction)
{ 
	Bullet* bullet = new Bullet;

	bullet->position = pos;

	Vector motion;

	motion.x = -speed * std::sin(Utils::DegToRads(direction));
	motion.y = speed * std::cos(Utils::DegToRads(direction));
	
	bullet->motion = motion;

	PE_GAME->entity_manager->AddEntity(bullet);
}