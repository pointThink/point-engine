#include "Entity.h"

#include <algorithm>
#include <iostream>

#include "Logging.h"
#include "Utils.h"

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
	removal_queue.push_back(std::find(entities.begin(), entities.end(), entity));
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
		// check collisions
		for (EntityBase* entity2 : entities)
		{
			/*
			// update collision objects of both entities
			entity->collision_group.UpdatePos(entity->position);
			entity2->collision_group.UpdatePos(entity->position);
			*/

			if ((entity->colidable && entity2->colidable) && (entity->position.GetDistanceTo(entity2->position) < entity->collision_group.max_check_distance && entity2->position.GetDistanceTo(entity->position) < entity2->collision_group.max_check_distance))
				if (entity->collision_group.CollidesWithGroup(&(entity2->collision_group)) && entity != entity2)
				{
					entity->OnCollision(entity2);
					entity2->OnCollision(entity);
				}
		}
		
		entity->Update();
	}

	for (std::vector<EntityBase*>::iterator entity_iter : removal_queue)
	{
		if (entity_iter != entities.end())
		{
			delete entities.at(std::distance(entities.begin(), entity_iter));
			entities.erase(entity_iter);

			removal_queue.erase(std::find(removal_queue.begin(), removal_queue.end(), entity_iter));
		}
	}
}

EntityBase* EntityManager::GetEntityByID(std::string id)
{
	for (EntityBase* entity : entities)
	{
		if (entity->GetUniqueID() == id)
		{
			return entity;
		}
	}

	PE::LogWarning("Could not find entity of id " + id);
	return NULL;
}