#include <PointEngine.h>
#include <UI/Widgets.h>

#include "Player.h"
#include "RandomSquare.h"

#include <random>
#include <ctime>

using namespace PE; 

Utils::Timer timer;
Utils::Timer timer2;

GameState::GameState* running;
GameState::GameState* paused;

void Quit()
{
	exit(0);
}

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
			
			if (PE_GAME_STATE == running)
				PE_GAME->SetCurrentGameState(paused, false);
			else
				PE_GAME->SetCurrentGameState(running, false);
		}
	}
}

void OnPress()
{
	PE_GAME->SetCurrentGameState(running, false);
}

int main()
{
	//srand(time(NULL));

	PE_GAME->Init();

	PE_GAME->ticksPerSecond = 60;

	PE_GAME->window->SetSize({1280, 720});

	running = new GameState::GameState;
	paused = new GameState::GameState;

	for (unsigned int i = 0; i < 20; i++)
	{
		running->entityManager->AddEntity(new RandomSquare());
	}

	
	running->entityManager->AddEntity(new Player());

	PE_GAME->inputManager->BindKey("move_sprint", PE_KEY_LEFT_SHIFT);
	PE_GAME->inputManager->BindKey("move_up", PE_KEY_W);
	PE_GAME->inputManager->BindKey("move_down", PE_KEY_S);
	PE_GAME->inputManager->BindKey("move_left", PE_KEY_A);
	PE_GAME->inputManager->BindKey("move_right", PE_KEY_D);
	PE_GAME->inputManager->BindButton("shoot", PE_MOUSE_LEFT);
	PE_GAME->inputManager->BindKey("pause", PE_KEY_ESCAPE);

	PE_GAME->SetEventHandler(&EventHandler);

	paused->uiManager->AddWidget("button2", new UI::Button("default", "Back in the game", { 20, 20 }, { 150, 50 }, &OnPress));
	paused->uiManager->AddWidget("button", new UI::Button("default", "Exit", { 20, 90 }, { 150, 50 }, &Quit));
	paused->uiManager->AddWidget("input", new UI::InputBox("default", { 50, 50 }, { 200, 100 }, "Hello"));

	//PE_GAME->window->SetFullscreen(true);

	PE_GAME->SetCurrentGameState(running, false);

	Hardware::CPUInfo cpuInfo;
	cpuInfo = Hardware::GetCPUInfo();

	LogInfo(cpuInfo.name);
	LogInfo("Cores: " + std::to_string(cpuInfo.coreCount));
	LogInfo("Threads: " + std::to_string(cpuInfo.threadCount) + "\n");

	Hardware::GPUInfo gpuInfo = Hardware::GetGPUInfo();

	LogInfo("GPU Name: " + gpuInfo.name);

	PE_GAME->Run();

	//Error::CriticalError("Shits fucked");

	return 0;
}