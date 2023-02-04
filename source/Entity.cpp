#include "Entity.h"

#include <algorithm>

#include "Logging.h"

using namespace PE::Entity;

void PE::Entity::EntityBase::Destroy()
{
	if (allow_extern_destruction)
		self_destruct = true;
	else
		PE::LogWarning("Cannot destroy entity because allow_extern_destruction is set to false");
}

std::string EntityBase::GetEntityName() {return entity_name;}
std::string EntityBase::GetUniqueID() {return unique_id;}

bool EntityBase::GetShouldSave() {return should_save;}
EntitySaveData EntityBase::GetSaveData() {return save_data;}

bool EntityBase::GetSelfDestruct() {return self_destruct;}
bool EntityBase::GetAllowExternDestruction() {return allow_extern_destruction;}

// -----------------------------------------------------------

void EntityManager::AddEntity(EntityBase * entity)
{
	// check if entity has an already used id - PT
	for (std::string unique_id : used_ids)
	{
		if (entity->GetUniqueID() == unique_id)
		{
			PE::LogWarning("Could not create entity because entity with same id exists!");
			return;
		}
	}

	entities.push_back(entity);
	used_ids.push_back(entity->GetUniqueID());
}

void EntityManager::DrawEntities()
{
	// sort entities by layer - PT
	std::sort(entities.begin(), entities.end());

	for (EntityBase * entity : entities)
	{
		entity->Draw();
	}
}

void EntityManager::UpdateEntities()
{
	for (EntityBase * entity : entities)
	{
		if (entity->GetSelfDestruct())
			entities.erase(std::find(entities.begin(), entities.end(), entity));
		else
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