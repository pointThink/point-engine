#pragma once

#include <string>

#include "Core.h"
#include "Window.h"
#include "Sprite.h"
#include "Entity.h"
#include "Utils.h"
#include "Event.h"
#include "Input.h"
#include "Console.h"

namespace PE
{
	class Console;

	class ENGINE_API Game
	{
		public:
		virtual void Init() final;
		virtual void Run() final;

		void SetGameName(std::string name);
		void SetGameVersion(std::string version);
		void SetContentPath(std::string path);
		void SetEventHandler(void (*event_handler)(EventType, EventParameters));

		float GetFrameTime();

		void QuitApplication();

		PE::Rendering::Window * window = NULL;
		PE::Rendering::SpriteManager * sprite_manager = NULL;
		PE::Entity::EntityManager * entity_manager = NULL;
		PE::InputManager * input_manager = NULL;

		PE::Console * console;

		private:
		void UpdateGameName();

		bool should_quit = false;
		bool initialized = false;

		std::string game_name;
		std::string game_version;
		std::string game_content_path;

		PE::Utils::Timer frame_timer;
		std::chrono::duration<float> delta_time;

		void Update();
		void Draw();
	};
}
