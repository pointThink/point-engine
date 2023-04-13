#include "RandomSquare.h"

#include <PointEngine.h>

#include "Bullet.h"

#include <random>

void RandomSquare::Init()
{
	entityName = "RandomSquare";

	position.x = rand() % 800;
	position.y = rand() % 600;

	color.r = rand() % 255;
	color.g = rand() % 255;
	color.b = rand() % 255;

	colidable = false;

	collisionGroup.maxCheckDistance = 50;

	Collision::CollisionBox* cb = new Collision::CollisionBox;

	cb->pos = position;
	cb->size = { 20, 20 };

	collisionGroup.AddObject("collider", cb);
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
		PE_GAME->entityManager->RemoveEntity(this);
}