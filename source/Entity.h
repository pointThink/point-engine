#pragma once

#include <vector>
#include <string>

#include "Core.h"
#include "Vector.h"

namespace PE
{
	class Game;

	namespace Entity
	{
		/*
		Not implemented but planned

		Simple method for knowing which data should be saved.
		It uses a key value system value system, where the key
		is an identifier for the data and the value is a pointer to
		where the data is located.

		The actual data is probably going to be just raw bytes.

		eg.
		/---------------------------------------\
		| key      | value                      |
		| ---------|----------------------------|
		| position | pointer to position vector |
		| motion   | pointer to motion vector   |
		\---------------------------------------/
		*/
		class ENGINE_API EntitySaveData
		{
			int testing;
		};

		class ENGINE_API EntityBase
		{
			protected:
			Game * game;

			std::string entity_name;
			std::string unique_id; //this is optional, only used for searching entities - PT

			bool should_save;
			PE::Entity::EntitySaveData save_data;

			int self_destruct = false; // destroy this entity if set to true - PT
			int allow_extern_destruction = true; // allow to destroy from outside the entity - PT

			public:
			int layer;

			Vector position;
			Vector motion;

			std::string GetEntityName();
			std::string GetUniqueID();

			void SetGameInstance(Game * game);

			bool GetShouldSave();
			PE::Entity::EntitySaveData GetSaveData();

			bool GetSelfDestruct();
			bool GetAllowExternDestruction();

			void Destroy();

			virtual void Init() = 0;
			virtual void Update() = 0;
			virtual void Draw() = 0;
			virtual void Use(EntityBase * user, std::string tag) = 0;

			// crap for sorting - PT
			bool operator < (const EntityBase& other)
			{
				return layer < other.layer;
			}

			bool operator > (const EntityBase& other)
			{
				return layer > other.layer;
			}
		};

		class ENGINE_API EntityManager
		{
			private:
			Game * game;

			std::vector<std::string> used_ids;
			std::vector<PE::Entity::EntityBase *> entities;

			public:
			EntityManager(Game * game);

			void AddEntity(EntityBase * entity);

			void UpdateEntities();
			void DrawEntities();

			PE::Entity::EntityBase* GetEntityByID(std::string id);
		};
	};
};
