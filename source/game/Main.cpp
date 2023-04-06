#include "PointEngine.h"

#include "SDL.h"

using namespace PE;

Rendering::Animation a;

class Player : public Entity::EntityBase
{
	void Init()
	{
		position = { 0, 0 };
		motion = { 0, 0 };
	}

	void Update()
	{
		motion = { 0, 0 };

		if (game->input_manager->GetKeyState(PE_KEY_W)->IsDown())
		{
			motion.y = -100;
		}


		if (game->input_manager->GetKeyState(PE_KEY_S)->IsDown())
		{
			motion.y = 100;
		}


		if (game->input_manager->GetKeyState(PE_KEY_A)->IsDown())
		{
			motion.x = -100;
		}


		if (game->input_manager->GetKeyState(PE_KEY_D)->IsDown())
		{
			motion.x = 100;
		}

		
	}

	void Draw()
	{
		game->window->camera_offset.x = -position.x + game->window->GetWidth() / 2;
		game->window->camera_offset.y = -position.y + game->window->GetHeight() / 2;
		game->window->DrawSquare({ position.x, position.y }, { 20, 20 }, { 255, 0, 255, 255 });

		game->font_manager->DrawString({ position.x + 20, position.y + 20 }, "default", "This is the player", Utils::Color(255, 0, 255, 255));
	}

};

void HandleEvent(EventType et, EventParameters ep)
{

	if (et == GAME_DRAW)
	{
		// a.UpdateCurrentFrame();

		Game::GetInstance()->window->DrawSquare({20, 20}, {20, 20}, {255, 0, 0, 255});
	}
	else if (et == GAME_UPDATE)
	{
		Game::GetInstance()->SetGameName(std::to_string(Game::GetInstance()->GetFrameTime()));
	}
}

int main()
{
	Game* game = Game::GetInstance();

	// a.AddSprite("test");
	// a.AddSprite("test2");
	
	// a.SetFramerate(10);

	game->Init();

	// game->sprite_manager->LoadSprite("test2.bmp", "test2");
	// game->sprite_manager->LoadSprite("test.bmp", "test");
	
	game->entity_manager->AddEntity(new Player);

	game->SetGameName("Test");
	game->SetEventHandler(&HandleEvent);

	game->Run();

	return 0;
}