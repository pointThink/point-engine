#include "Entity.h"

#include <algorithm>
#include <iostream>

#include "Logging.h"
#include "Utils/Utils.h"

using namespace PE::Entity;

class LessThanKey
{
	public:
	inline bool operator() (const EntityBase* struct1, const EntityBase* struct2)
	{
		return (struct1->layer < struct2->layer);
	}
};

void PE::Entity::EntityBase::SetGameInstance(Game* game)
{
	this->game = game;
}

std::string EntityBase::GetEntityName() {return entityName;}
std::string EntityBase::GetUniqueID() {return uniqueId;}

// -----------------------------------------------------------

EntityManager::EntityManager(Game* game)
{
	this->game = game;
}

void EntityManager::AddEntity(EntityBase* entity)
{
	// check if entity has an already used id - PT
	for (std::string unique_id : usedIds)
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
	usedIds.push_back(entity->GetUniqueID());
}

void EntityManager::RemoveEntity(EntityBase* entity)
{
	std::vector<EntityBase*>::iterator it = std::find(entities.begin(), entities.end(), entity);
	unsigned int index = std::distance(entities.begin(), it);
	
	entities.at(index)->shouldDestroy = true;
}

void EntityManager::DrawEntities()
{
	// sort entities by layer - PT
	std::sort(entities.begin(), entities.end(), LessThanKey());

	for (EntityBase* entity : entities)
	{
		entity->Draw();
	}
}

void EntityManager::UpdateEntities()
{
	for (unsigned int i = 0; i < entities.size();)
	{		
		EntityBase* entity = entities[i];

		if (!entity->shouldDestroy)
		{
			entity->position.x = entity->position.x + (entity->motion.x * game->GetFrameTime());
			entity->position.y = entity->position.y + (entity->motion.y * game->GetFrameTime());

			entity->Update();
			i++;
		}
		else
			entities.erase(entities.begin() + i);
	}
}

void EntityManager::TickEntities()
{
	for (unsigned int i = 0; i < entities.size();)
	{
		EntityBase* entity = entities[i];

		/*
		if (std::find(entities.begin(), entities.end(), entity) == entities.end())
		{
			break;
		}
		*/

		/*
		check collisions
		for now this code is disabled because it runs like shit
		collision is left up to the game dev for now
		*/

		/*
		for (EntityBase* entity2 : entities)
		{
			
			// update collision objects of both entities
			entity->collision_group.UpdatePos(entity->position);
			entity2->collision_group.UpdatePos(entity->position);

			if ((entity->colidable && entity2->colidable))
				if (entity->position.GetDistanceTo(entity2->position) < entity->collision_group.max_check_distance && entity2->position.GetDistanceTo(entity->position) < entity2->collision_group.max_check_distance)
				{
					if (entity->collision_group.CollidesWithGroup(&(entity2->collision_group)) && entity != entity2)
					{
						entity->OnCollision(entity2);
						entity2->OnCollision(entity);
					}
				}
		}
		*/

		entity->Tick();
		i++;
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

unsigned int EntityManager::GetEntityCount()
{
	return entities.size();
}