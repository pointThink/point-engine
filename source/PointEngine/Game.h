#pragma once

#define PE_GAME PE::Game::GetInstance()
#define PE_GAME_STATE PE::Game::GetInstance()->GetCurrentGameState()

#include <string>

#include "Core.h"
#include "Rendering/Window.h"
#include "Rendering/Sprite.h"
#include "Entity/Entity.h"
#include "Utils/Utils.h"
#include "Event.h"
#include "Input.h"
#include "Console/Console.h"
#include "Lighting.h"
#include "Rendering/Font.h"
#include "Utils/Performace.h"
#include "Utils/RNG.h"
#include "UI/UIManager.h"
#include "Gamestate/Gamestate.h"

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

		// GameState related stuff

		void SetCurrentGameState(GameState::GameState* state, bool deleteOld);
		GameState::GameState* GetCurrentGameState();

		void QuitApplication();

		// PE::Lighting::LightingManager* lightManager = NULL;
		PE::Rendering::Window* window = NULL;
		PE::Rendering::SpriteManager* spriteManager = NULL;
		PE::InputManager* inputManager = NULL;
		PE::Console* console = NULL;
		PE::Font::FontManager* fontManager = NULL;
		PE::Performance::PerformanceProfiler* performanceProfiler = NULL;
		PE::Random::RNG* rng = NULL;
		
		bool isPaused = false;
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

		GameState::GameState* currentGameState = nullptr;

		void Update();
		void Draw();
		void Tick();
	};
}
