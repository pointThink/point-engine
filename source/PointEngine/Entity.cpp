#include "Entity.h"

#include <algorithm>
#include <iostream>

#include "Logging.h"

using namespace PE::Entity;

void PE::Entity::EntityBase::SetGameInstance(Game* game)
{
	this->game = game;
}

std::string EntityBase::GetEntityName() {return entity_name;}
std::string EntityBase::GetUniqueID() {return unique_id;}

// -----------------------------------------------------------

EntityManager::EntityManager(Game* game)
{
	this->game = game;
}

void EntityManager::AddEntity(EntityBase* entity)
{
	// check if entity has an already used id - PT
	for (std::string unique_id : used_ids)
	{
		if (entity->GetUniqueID() == unique_id && entity->GetUniqueID() != "")
		{
			PE::LogWarning("Could not create entity because entity with same id exists!");
			return;
		}
	}

	entity->SetGameInstance(game);
	entity->Init();

	entities.push_back(entity);
	used_ids.push_back(entity->GetUniqueID());
}

void EntityManager::RemoveEntity(EntityBase* entity)
{
	entities.erase(std::find(entities.begin(), entities.end(), entity));
	delete entity;
}

void EntityManager::DrawEntities()
{
	// sort entities by layer - PT
	//std::sort(entities.begin(), entities.end(), );

	for (EntityBase* entity : entities)
	{
		entity->Draw();
	}
}

void EntityManager::UpdateEntities()
{
	for (EntityBase* entity : entities)
	{
		entity->position.x = entity->position.x + (entity->motion.x * game->GetFrameTime());
		entity->position.y = entity->position.y + (entity->motion.y * game->GetFrameTime());

		entity->Update();
	}
}

EntityBase * EntityManager::GetEntityByID(std::string id)
{
	for (EntityBase * entity : entities)
	{
		if (entity->GetUniqueID() == id)
		{
			return entity;
		}
	}

	PE::LogWarning("Could not find entity of id " + id);
	return NULL;
}
