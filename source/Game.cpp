#include "Game.h"

#include "SDL2\SDL.h"
#include "Logging.h"

namespace PE
{
	void Game::Run()
	{
		// Shameless plug
		LogInfo(game_name + " " + game_version + " running on PointEngine version " + PE_VERSION);

		window = new PE::Rendering::Window("Test", 800, 600, false);
		sprite_manager = new PE::Rendering::SpriteManager(window, "./content");

		sprite_manager->LoadSprite("test.bmp", "test");

		while (!should_quit)
		{
			Update();
			Draw();
		}

        PE::LogInfo("Quitting");

		sprite_manager->RemoveSprite("test");

		delete window;
	}

	void Game::Update()
	{
		// Handle some SDL events
		SDL_Event event;

		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				should_quit = true;
			}
		}
	}

	void Game::Draw()
	{
		SDL_RenderClear(window->GetSDLRenderer());

        sprite_manager->DrawSprite("test", 10, 10);

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
}
