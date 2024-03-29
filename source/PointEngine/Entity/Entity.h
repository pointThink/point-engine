#pragma once

#include <vector>
#include <string>

#include "Core.h"
#include "Vector.h"
#include "Collision.h"

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
			
		};

		class ENGINE_API EntityBase
		{
		protected:
			Game* game;

			std::string entityName;
			std::string uniqueId; // this is optional, only used for searching entities - PT

		public:
			bool shouldDestroy = false;
			bool colidable = false;
			Collision::CollisionGroup collisionGroup;

			int layer = 0;

			Vector position = { 0, 0 };
			Vector motion = { 0, 0 };

			std::string GetEntityName();
			std::string GetUniqueID();

			void SetGameInstance(Game* game);

			virtual void Init() {}
			virtual void Update() {}
			virtual void Draw() {}
			virtual void Tick() {}

			virtual void OnCollision(EntityBase* other_entity) {}
			virtual void Use(EntityBase* user, std::string tag) {}

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
			Game* game = nullptr;

			std::vector<std::string> usedIds;
			std::vector<PE::Entity::EntityBase*> entities;

			public:
			EntityManager(Game* game);

			void AddEntity(EntityBase* entity);
			void RemoveEntity(EntityBase* entity);

			void UpdateEntities();
			void TickEntities();
			void DrawEntities();

			void ShowEntityInspector();

			unsigned int GetEntityCount();

			PE::Entity::EntityBase* GetEntityByID(std::string id);

			// why do i need to declare it in the header C++ why?
			template<typename T>
			std::vector<T*> GetEntitiesByType()
			{
				std::vector<T*> retEntities;

				for (EntityBase* entity : entities)
				{
					if (instanceof<T>(entity))
					{
						retEntities.push_back((T*)entity);
					}
				}

				return retEntities;
			};
		};
	};
};
