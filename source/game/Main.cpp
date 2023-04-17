#include <PointEngine.h>
#include <UI/Widgets.h>

#include "Player.h"
#include "RandomSquare.h"

#include <random>
#include <ctime>

using namespace PE; 

Utils::Timer timer;
Utils::Timer timer2;

void EventHandler(EventType et, EventParameters ep)
{
	if (et == GAME_UPDATE)
	{
		if (timer.HasTimeElapsed(0.5))
		{
			Game::GetInstance()->SetGameName(std::to_string(1 / Game::GetInstance()->GetFrameTime()));
			timer.Reset();
		}

		if (PE_GAME->inputManager->GetBindState("pause")->IsDown() && timer2.HasTimeElapsed(0.599))
		{
			LogInfo("Key pressed");
			timer2.Reset();
			PE_GAME->isPaused = !PE_GAME->isPaused;
		}
	}
}

void OnPress()
{
	LogInfo("PRessed");
}

int main()
{
	//srand(time(NULL));

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
	PE_GAME->inputManager->BindKey("pause", PE_KEY_ESCAPE);

	PE_GAME->SetEventHandler(&EventHandler);

	PE_GAME->uiManager->AddWidget("button", new UI::Button("default", "test", { 20, 20 }, { 150, 50 }, &OnPress));
	PE_GAME->uiManager->AddWidget("checkbox", new UI::CheckBox("default", "test", { 200, 20 }, { 25, 25 }));
	PE_GAME->uiManager->AddWidget("label", new UI::Label({ 255, 255 }, "default", "This is a label", { 0, 0, 0, 255 }));


	PE_GAME->Run();

	return 0;
}