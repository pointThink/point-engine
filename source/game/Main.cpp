#include "PointEngine.h"

#include "SDL.h"

using namespace PE;

Rendering::Animation a;

void HandleEvent(EventType et, EventParameters ep)
{

	if (et == GAME_DRAW)
	{
		a.UpdateCurrentFrame();

		Game::GetInstance()->sprite_manager->DrawSprite(a.GetCurrentSprite(), {20, 20});
	}
	else if (et == GAME_UPDATE)
	{
		
	}
}

int main()
{
	Game * game = Game::GetInstance();

	a.AddSprite("test");
	a.AddSprite("test2");
	
	a.SetFramerate(10);

	game->Init();

	game->sprite_manager->LoadSprite("test2.bmp", "test2");
	game->sprite_manager->LoadSprite("test.bmp", "test");
	

	game->SetGameName("Test");
	game->SetEventHandler(&HandleEvent);

	game->Run();
}