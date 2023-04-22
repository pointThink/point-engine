#include "RandomSquare.h"

#include <PointEngine.h>

#include "Bullet.h"

#include <random>

void RandomSquare::Init()
{
	entityName = "RandomSquare";

	position.x = game->rng->RandomNumber(0, 800);
	position.y = game->rng->RandomNumber(0, 600);

	color.r = game->rng->RandomNumber(0, 255);
	color.g = game->rng->RandomNumber(0, 255);
	color.b = game->rng->RandomNumber(0, 255);

	colidable = true;

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
		PE_GAME_STATE->entityManager->RemoveEntity(this);
}