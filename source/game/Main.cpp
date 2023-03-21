#include "PointEngine.h"

using namespace PE;

void HandleEvent(EventType et, EventParameters ep)
{
	if (et == GAME_UPDATE)
	{
		Game::GetInstance()->sprite_manager->DrawSprite("test", {20, 20});
	}
}

int main()
{
	Game * game = Game::GetInstance();


	game->Init();

	game->SetGameName("Test");
	game->SetEventHandler(&HandleEvent);

	game->Run();
}