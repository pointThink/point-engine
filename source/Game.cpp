#include "Game.h"

#include "SDL2\SDL.h"
#include "Logging.h"
#include "Utils.h"
#include "Event.h"

#include <iostream>

namespace PE
{
	void Game::Init()
	{
		PE::LogInit();

		// Shameless plug - PT
		LogInfo(game_name + " " + game_version + " running on PointEngine version " + PE_VERSION);

		window = new PE::Rendering::Window("Test", 800, 600, false);
		sprite_manager = new PE::Rendering::SpriteManager(window, "./content/");
		entity_manager = new PE::Entity::EntityManager;

		PE::CallEventFunction(PE::GAME_INIT, PE::EventParameters(0, 0, {0, 0}));
	}

	void Game::Run()
	{
		while (!should_quit)
		{
			delta_time = frame_timer.GetTime();
			frame_timer.Reset();

			Update();
			Draw();
		}

		PE::CallEventFunction(PE::GAME_CLOSED, PE::EventParameters(0, 0, {0, 0}));
        PE::LogInfo("Quitting");

        PE::LogDeInit();

		delete window;
	}

	void Game::Update()
	{
		// Handle some SDL events - PT
		SDL_Event event;

		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				should_quit = true;
			}
		}

		entity_manager->UpdateEntities();

		PE::CallEventFunction(PE::GAME_UPDATE, PE::EventParameters(0, 0, {0, 0}));
	}

	void Game::Draw()
	{
		SDL_RenderClear(window->GetSDLRenderer());

		entity_manager->DrawEntities();
		SDL_RenderPresent(window->GetSDLRenderer());
	}

	void Game::QuitApplication()
	{
		should_quit = true;
	}

	void Game::SetGameName(std::string name)
	{
		game_name = name;
		SDL_SetWindowTitle(window->GetSDLWindow(), name.c_str());
	}

	void Game::SetGameVersion(std::string version)
	{
		game_version = version;
	}

	void Game::SetContentPath(std::string path)
	{
		game_content_path = path;
	}

	void Game::SetEventHandler(void (*event_handler)(EventType, EventParameters))
	{
		PE::event_handler = event_handler;
	}

	float Game::GetFrameTime()
	{
		return delta_time.count();
	}
}
