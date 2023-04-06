#pragma once

#define PE_GAME PE::Game::GetInstance()

#include <string>

#include "Core.h"
#include "Window.h"
#include "Sprite.h"
#include "Entity.h"
#include "Utils.h"
#include "Event.h"
#include "Input.h"
#include "Console.h"
#include "Lighting.h"
#include "Font.h"

namespace PE
{
	class Console;

	class ENGINE_API Game
	{
		public:

		// Get game singleton
		static Game* GetInstance();

		virtual void Init() final;
		virtual void Run() final;

		void SetGameName(std::string name);
		void SetGameVersion(std::string version);
		void SetContentPath(std::string path);
		void SetEventHandler(void (*event_handler)(EventType, EventParameters));

		float GetFrameTime();

		void QuitApplication();

		PE::Lighting::LightingManager* light_manager = NULL;
		PE::Rendering::Window* window = NULL;
		PE::Rendering::SpriteManager* sprite_manager = NULL;
		PE::Entity::EntityManager* entity_manager = NULL;
		PE::InputManager* input_manager = NULL;
		PE::Console* console = NULL;
		PE::Font::FontManager* font_manager = NULL;

		std::string game_content_path;

		private:
		void UpdateGameName();

		bool lighting_enabled = false;

		bool should_quit = false;
		bool initialized = false;

		static Game* instance;

		std::string game_name;
		std::string game_version;

		PE::Utils::Timer frame_timer;
		std::chrono::duration<float> delta_time;

		void Update();
		void Draw();
	};
}
