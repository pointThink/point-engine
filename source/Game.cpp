#include "Game.h"

#include "SDL2/SDL.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_sdlrenderer.h"
#include "Logging.h"
#include "Utils.h"
#include "Event.h"
#include "Input.h"
#include "Console.h"

#include <iostream>
//using namespace PE;

namespace PE
{
	void Game::Init()
	{
		console = new PE::Console(this);
		PE::LogInit(console);

		// Shameless plug - PT
		LogInfo("Game version " + game_version + " running on PointEngine version " + PE_VERSION);

		window = new PE::Rendering::Window("Test", 800, 600, false);
		sprite_manager = new PE::Rendering::SpriteManager(window, "./content/");
		entity_manager = new PE::Entity::EntityManager(this);

		input_manager = new PE::InputManager;

		// initialize the imgui library - PT
		ImGui::CreateContext();
		ImGuiIO & io = ImGui::GetIO(); (void) io;
		ImGui::StyleColorsDark();
		ImGui_ImplSDL2_InitForSDLRenderer(window->GetSDLWindow(), window->GetSDLRenderer());
		ImGui_ImplSDLRenderer_Init(window->GetSDLRenderer());


		// load a font that dosent suck as much as the default - PT
		io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/CascadiaCode.ttf", 14);

		ImGui::GetStyle().WindowRounding = 6;
		ImGui::GetStyle().ChildRounding = 6;
		ImGui::GetStyle().FrameRounding = 6;

		// define some engine convars
		// console->convar_manager->RegisterConVar("g_title", ConVar(CONVAR_STRING, &game_name, MethodPointer<PE::Game>(this, &UpdateGameName)));
		console->convar_manager->RegisterConVar("g_version", ConVar(CONVAR_STRING, &game_version));

		console->convar_manager->RegisterConVar("r_bg_color_r", ConVar(CONVAR_INT, &window->bg_color.r));
		console->convar_manager->RegisterConVar("r_bg_color_g", ConVar(CONVAR_INT, &window->bg_color.g));
		console->convar_manager->RegisterConVar("r_bg_color_b", ConVar(CONVAR_INT, &window->bg_color.b));


		PE::CallEventFunction(PE::GAME_INIT, PE::EventParameters(0, 0, {0, 0}));

		initialized = true;
	}

	void Game::Run()
	{
		if (!initialized)
		{
			LogError("Engine not initialized properly or not at all, cehck if Game::Init() was ran anywhere or if any errors occured during initialization");
			PE::CallEventFunction(PE::GAME_CLOSED, PE::EventParameters(0, 5, { 0, 0 }));
			exit(5);
		}

		while (!should_quit)
		{
			delta_time = frame_timer.GetTime();
			frame_timer.Reset();

			Update();
			Draw();
		}

		PE::CallEventFunction(PE::GAME_CLOSED, PE::EventParameters(0, 0, {0, 0}));
        PE::LogInfo("Quitting");

        PE::LogDeInit();

		delete window;
		delete entity_manager;
		delete sprite_manager;
	}

	void Game::Update()
	{
		// Handle some SDL events - PT
		SDL_Event event;

		while (SDL_PollEvent(&event) != 0)
		{
			ImGui_ImplSDL2_ProcessEvent(&event);

			switch (event.type)
			{
				case SDL_QUIT:
					should_quit = true;
					break;

				case SDL_KEYDOWN:
					if (event.key.keysym.scancode == 53) // ~ key is reserved for opening the console - PT
						console->is_open = !console->is_open;

					if (!console->is_open)
						input_manager->GetKeyState(event.key.keysym.scancode)->SetDown(true);
					break;

				case SDL_KEYUP:
					if (!console->is_open)
						input_manager->GetKeyState(event.key.keysym.scancode)->SetDown(false);
					break;

				case SDL_MOUSEBUTTONDOWN:
					if (!console->is_open)
						input_manager->GetButtonState(event.button.button)->SetDown(true);
					break;

				case SDL_MOUSEBUTTONUP:
					if (!console->is_open)
						input_manager->GetButtonState(event.button.button)->SetDown(false);
					break;

				case SDL_MOUSEMOTION:
					if (!console->is_open)
						input_manager->SetMousePos(event.motion.x, event.motion.y);
			}
		}

		input_manager->UpdateLastFrameStates();

		entity_manager->UpdateEntities();

		PE::CallEventFunction(PE::GAME_UPDATE, PE::EventParameters(0, 0, {0, 0}));
	}

	void Game::Draw()
	{
		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		window->ClearBackground();

		PE::CallEventFunction(PE::GAME_DRAW, PE::EventParameters(0, 0, { 0, 0 }));
		entity_manager->DrawEntities();

		if (console->is_open)
			console->Draw();

		ImGui::Render();
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());

		window->PresentRenderer();
	}

	void Game::QuitApplication()
	{
		should_quit = true;
	}

	void Game::SetGameName(std::string name)
	{
		game_name = name;
		SDL_SetWindowTitle(window->GetSDLWindow(), name.c_str());
	}

	void Game::SetGameVersion(std::string version)
	{
		game_version = version;
	}

	void Game::SetContentPath(std::string path)
	{
		game_content_path = path;
	}

	void Game::SetEventHandler(void (*event_handler)(EventType, EventParameters))
	{
		PE::event_handler = event_handler;
	}

	float Game::GetFrameTime()
	{
		return delta_time.count();
	}

	void Game::UpdateGameName()
	{
		window->SetTitle(game_name);
	}
}
