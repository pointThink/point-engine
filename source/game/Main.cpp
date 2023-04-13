#include <PointEngine.h>

#include "Player.h"
#include "RandomSquare.h"

#include <random>
#include <ctime>

using namespace PE; 

void EventHandler(EventType et, EventParameters ep)
{
	if (et == GAME_UPDATE)
	{
		Game::GetInstance()->SetGameName(std::to_string(1 / Game::GetInstance()->GetFrameTime()));
	}
}

int main()
{
	srand(time(NULL));

	PE_GAME->Init();

	PE_GAME->ticksPerSecond = 60;

	PE_GAME->window->SetSize(1366, 768);

	for (unsigned int i = 0; i < 20; i++)
	{
		PE_GAME->entityManager->AddEntity(new RandomSquare());
	}

	PE_GAME->entityManager->AddEntity(new Player());

	PE_GAME->inputManager->BindKey("move_sprint", PE_KEY_LSHIFT);
	PE_GAME->inputManager->BindKey("move_up", PE_KEY_W);
	PE_GAME->inputManager->BindKey("move_down", PE_KEY_S);
	PE_GAME->inputManager->BindKey("move_left", PE_KEY_A);
	PE_GAME->inputManager->BindKey("move_right", PE_KEY_D);
	PE_GAME->inputManager->BindButton("shoot", PE_MOUSE_LEFT);

	PE_GAME->SetEventHandler(&EventHandler);

	PE_GAME->Run();

	return 0;
}