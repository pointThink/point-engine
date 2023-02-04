#include "Game.h"

#include "SDL2\SDL.h"
#include "Logging.h"
#include "Utils.h"

#include <iostream>

namespace PE
{
	void Game::Init()
	{
		// Shameless plug - PT
		LogInfo(game_name + " " + game_version + " running on PointEngine version " + PE_VERSION);

		window = new PE::Rendering::Window("Test", 800, 600, false);
		sprite_manager = new PE::Rendering::SpriteManager(window, "./content");
		entity_manager = new PE::Entity::EntityManager;
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

        PE::LogInfo("Quitting");

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
	}

	void Game::SetGameVersion(std::string version)
	{
		game_version = version;
	}

	void Game::SetContentPath(std::string path)
	{
		game_content_path = path;
	}

	float Game::GetFrameTime()
	{
		return delta_time.count();
	}
}
