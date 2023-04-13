#include "RandomSquare.h"

#include <PointEngine.h>

#include "Bullet.h"

#include <random>

void RandomSquare::Init()
{
	entity_name = "RandomSquare";

	position.x = rand() % 800;
	position.y = rand() % 600;

	color.r = rand() % 255;
	color.g = rand() % 255;
	color.b = rand() % 255;

	colidable = false;

	collision_group.max_check_distance = 50;

	Collision::CollisionBox* cb = new Collision::CollisionBox;

	cb->pos = position;
	cb->size = { 20, 20 };

	collision_group.AddObject("collider", cb);
}

void RandomSquare::Draw()
{
	PE_GAME->window->DrawSquare(position, { 20, 20 }, color);
}

void RandomSquare::Update()
{
	
}

void RandomSquare::OnCollision(Entity::EntityBase* entity)
{
	if (instanceof<Bullet>(entity))
		PE_GAME->entity_manager->RemoveEntity(this);
}