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
#include "Performace.h"

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
		void SetEventHandler(void (*eventHandler)(EventType, EventParameters));

		float GetFrameTime();

		void QuitApplication();

		PE::Lighting::LightingManager* lightManager = NULL;
		PE::Rendering::Window* window = NULL;
		PE::Rendering::SpriteManager* spriteManager = NULL;
		PE::Entity::EntityManager* entityManager = NULL;
		PE::InputManager* inputManager = NULL;
		PE::Console* console = NULL;
		PE::Font::FontManager* fontManager = NULL;
		PE::Performace::PerformanceProfiler* performanceProfiler = NULL;

		int ticksPerSecond = 60;
		std::string gameContentPath;

		private:
		void UpdateGameName();

		bool lightingEnabled = false;

		bool shouldQuit = false;
		bool initialized = false;

		static Game* instance;

		std::string gameName;
		std::string gameVersion;

		PE::Utils::Timer frameTimer;
		PE::Utils::Timer tickTimer;
		std::chrono::duration<float> deltaTime = std::chrono::milliseconds(1);

		void Update();
		void Draw();
		void Tick();
	};
}
