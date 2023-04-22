#pragma once

#include "Core.h"
#include "Entity/Entity.h"
#include "UI/UIManager.h"

namespace PE
{
	namespace GameState
	{
		class ENGINE_API  GameState
		{
		public:
			Entity::EntityManager* entityManager = nullptr;
			UI::UIManager* uiManager = nullptr;

			GameState();
			~GameState();

			virtual void Init() {}
			virtual void DeInit() {}

			virtual void OnDraw() {}
			virtual void OnUpdate() {}
			virtual void OnTick() {}
		};
	}
}