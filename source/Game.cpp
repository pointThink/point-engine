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

		while (true)
		{
			Update();
			Draw();
		}

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
}