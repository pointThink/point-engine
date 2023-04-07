#include "Game.h"

#include "SDL.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer.h"
#include "Logging.h"
#include "Utils.h"
#include "Event.h"
#include "Input.h"
#include "Console.h"
#include "Font.h"
#include "Performace.h"

#include <iostream>
//using namespace PE;

namespace PE
{
	Game* Game::instance = nullptr;

	Game* Game::GetInstance()
	{
		if (instance == nullptr)
			instance = new Game();

		return instance;
	}

	void Game::Init()
	{
		console = new PE::Console(this);
		PE::LogInit(console);

		// Shameless plug - PT
		LogInfo("Game version " + game_version + " running on PointEngine version " + PE_VERSION);

		window = new PE::Rendering::Window("PointEngine game", 800, 600, false);
		sprite_manager = new PE::Rendering::SpriteManager(window);
		entity_manager = new PE::Entity::EntityManager(this);
		input_manager = new PE::InputManager;
		light_manager = new PE::Lighting::LightingManager(5, Vector(window->GetWidth(), window->GetHeight()));
		font_manager = new PE::Font::FontManager;
		performance_profiler = new PE::Performace::PerformanceProfiler;

		// load the default font
		font_manager->LoadExternalFont("default", "C:/Windows/Fonts/consola.ttf", 14);

		// initialize the imgui library - PT
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplSDL2_InitForSDLRenderer(window->GetSDLWindow(), window->GetSDLRenderer());
		ImGui_ImplSDLRenderer_Init(window->GetSDLRenderer());


		// load a font that dosent suck as much as the default - PT
		io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/consola.ttf", 14);

		ImGui::GetStyle().WindowRounding = 6;
		ImGui::GetStyle().ChildRounding = 6;
		ImGui::GetStyle().FrameRounding = 6;

		// define some engine convars
		// console->convar_manager->RegisterConVar("g_title", ConVar(CONVAR_STRING, &game_name, MethodPointer<PE::Game>(this, &UpdateGameName)));
		console->convar_manager->RegisterConVar("g_version", ConVar(CONVAR_STRING, &game_version));

		console->convar_manager->RegisterConVar("r_bg_color_r", ConVar(CONVAR_INT, &window->bg_color.r));
		console->convar_manager->RegisterConVar("r_bg_color_g", ConVar(CONVAR_INT, &window->bg_color.g));
		console->convar_manager->RegisterConVar("r_bg_color_b", ConVar(CONVAR_INT, &window->bg_color.b));
		console->convar_manager->RegisterConVar("r_lighting_enabled", ConVar(CONVAR_BOOL, &lighting_enabled));

		PE::CallEventFunction(PE::GAME_INIT, PE::EventParameters(0, 0, { 0, 0 }));

		initialized = true;

		light_manager->CreateCellArray({ double(window->GetWidth()), double(window->GetHeight()) }, 5);

		if (lighting_enabled)
		{
			light_manager->CreateLightSource({ 400, 300 }, { 0, 255, 0, 255 }, 300);
			light_manager->CreateLightSource({ 780, 590 }, { 0, 0, 255, 255 }, 300);
			light_manager->CreateLightSource({ 20, 10 }, { 255, 0, 0, 255 }, 300);
		}

		LogInfo(std::to_string(double(window->GetWidth())) + std::to_string(double(window->GetHeight())));
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

			performance_profiler->Begin("tick");
			// check if should tick
			if (tick_timer.HasTimeElapsed(1.0 / ticks_per_second))
			{
				Tick();
				tick_timer.Reset();
			}
			performance_profiler->End();

			Draw();

			performance_profiler->Clear();
		}

		PE::CallEventFunction(PE::GAME_CLOSED, PE::EventParameters(0, 0, {0, 0}));
        PE::LogInfo("Quitting");

        PE::LogDeInit();

        PE::LogInfo("Deinitializing window");
		delete window;
		PE::LogInfo("Deinitializing entity manager");
		delete entity_manager;
		PE::LogInfo("Deinitializing sprite manager");
		delete sprite_manager;

		PE::LogInfo("Deinitialized everything");
	}

	void Game::Update()
	{
		// Handle some SDL events - PT
		SDL_Event event;

		performance_profiler->Begin("SDL_event_handling");
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

		performance_profiler->End();

		performance_profiler->Begin("input_last_frame_state_update");
		input_manager->UpdateLastFrameStates();
		performance_profiler->End();

		performance_profiler->Begin("entity_update");
		entity_manager->UpdateEntities();
		performance_profiler->End();

		PE::CallEventFunction(PE::GAME_UPDATE, PE::EventParameters(0, 0, {0, 0}));
	}

	void Game::Tick()
	{
		entity_manager->TickEntities();
	}

	void Game::Draw()
	{
		window->bg_color = { 255, 255, 255, 255 };

		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		window->ClearBackground();

		PE::CallEventFunction(PE::GAME_DRAW, PE::EventParameters(0, 0, { 0, 0 }));


		performance_profiler->Begin("entity_drawing");
		entity_manager->DrawEntities();
		performance_profiler->End();

		// light_manager->CastLightRay({50, 50}, Utils::Color(255, 255, 255, 255), 1000, 100);

		if (lighting_enabled)
		{
			performance_profiler->Begin("lighting");

			SDL_Texture* light_map = light_manager->GenerateLightMap();
			SDL_SetTextureBlendMode(light_map, SDL_BLENDMODE_MUL);

			SDL_RenderCopy(window->GetSDLRenderer(), light_map, NULL, NULL);

			performance_profiler->End();
		}

		Vector old_cam_offset = window->camera_offset;
		window->camera_offset = { 0, 0 };

		if (console->is_open)
		{
			console->Draw();

			std::map<double, std::string> timings = performance_profiler->GetTimings();

			unsigned int iter = 1;
			for (auto [key, val] : timings)
			{
				font_manager->DrawString({14, double(14 * iter + 3) }, "default", val + ": " + std::to_string(key), Utils::Color(255, 0, 0, 255));
				iter++;
			}
		}

		window->camera_offset = old_cam_offset;

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
		path = "./" + path;

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
