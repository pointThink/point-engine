#include "PointEngine.h"

#include "SDL.h"

using namespace PE;

Rendering::Animation a;

class Player : public Entity::EntityBase
{
	void Init()
	{
		position = { 400, 300 };
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
		game->window->DrawSquare(position, { 20, 20 }, { 255, 0, 255, 255 });
	}

};

void HandleEvent(EventType et, EventParameters ep)
{

	if (et == GAME_DRAW)
	{
		// a.UpdateCurrentFrame();

		// Game::GetInstance()->sprite_manager->DrawSprite(a.GetCurrentSprite(), {20, 20});
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