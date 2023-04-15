#include "Game.h"

#include "SDL.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer.h"
#include "Logging.h"
#include "Event.h"
#include "Input.h"
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
		LogInfo("Game version " + gameVersion + " running on PointEngine version " + PE_VERSION);

		window = new PE::Rendering::Window("PointEngine game", 800, 600, false);
		spriteManager = new PE::Rendering::SpriteManager(window);
		entityManager = new PE::Entity::EntityManager(this);
		inputManager = new PE::InputManager;
		lightManager = new PE::Lighting::LightingManager(5, Vector(window->GetWidth(), window->GetHeight()));
		fontManager = new PE::Font::FontManager;
		performanceProfiler = new PE::Performace::PerformanceProfiler;
		rng = new PE::Random::RNG;

		// load the default font
		fontManager->LoadExternalFont("default", "C:/Windows/Fonts/consola.ttf", 14);

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
		// console->convarManager->RegisterConVar("g_title", ConVar(CONVAR_STRING, &gameName, MethodPointer<PE::Game>(this, &UpdateGameName)));
		console->convarManager->RegisterConVar("g_version", ConVar(CONVAR_STRING, &gameVersion));

		console->convarManager->RegisterConVar("r_bg_color_r", ConVar(CONVAR_INT, &window->bg_color.r));
		console->convarManager->RegisterConVar("r_bg_color_g", ConVar(CONVAR_INT, &window->bg_color.g));
		console->convarManager->RegisterConVar("r_bg_color_b", ConVar(CONVAR_INT, &window->bg_color.b));
		console->convarManager->RegisterConVar("r_lightingEnabled", ConVar(CONVAR_BOOL, &lightingEnabled));

		PE::CallEventFunction(PE::GAME_INIT, PE::EventParameters(0, 0, { 0, 0 }));

		initialized = true;

		lightManager->CreateCellArray({ double(window->GetWidth()), double(window->GetHeight()) }, 5);

		if (lightingEnabled)
		{
			lightManager->CreateLightSource({ 400, 300 }, { 0, 255, 0, 255 }, 300);
			lightManager->CreateLightSource({ 780, 590 }, { 0, 0, 255, 255 }, 300);
			lightManager->CreateLightSource({ 20, 10 }, { 255, 0, 0, 255 }, 300);
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

		while (!shouldQuit)
		{
			deltaTime = frameTimer.GetTime();
			frameTimer.Reset();

			Update();

			performanceProfiler->Begin("tick");
			// check if should tick
			if (tickTimer.HasTimeElapsed(1.0 / ticksPerSecond))
			{
				Tick();
				tickTimer.Reset();
			}
			performanceProfiler->End();

			Draw();

			performanceProfiler->Clear();
		}

		PE::CallEventFunction(PE::GAME_CLOSED, PE::EventParameters(0, 0, {0, 0}));
        PE::LogInfo("Quitting");

        PE::LogDeInit();

        PE::LogInfo("Deinitializing window");
		delete window;
		PE::LogInfo("Deinitializing entity manager");
		delete entityManager;
		PE::LogInfo("Deinitializing sprite manager");
		delete spriteManager;

		PE::LogInfo("Deinitialized everything");
	}

	void Game::Update()
	{
		// Handle some SDL events - PT
		SDL_Event event;

		performanceProfiler->Begin("SDL_event_handling");
		while (SDL_PollEvent(&event) != 0)
		{
			ImGui_ImplSDL2_ProcessEvent(&event);

			switch (event.type)
			{
				case SDL_QUIT:
					shouldQuit = true;
					break;

				case SDL_KEYDOWN:
					if (event.key.keysym.scancode == 53) // ~ key is reserved for opening the console - PT
						console->isOpen = !console->isOpen;

					if (!console->isOpen)
						inputManager->GetKeyState(event.key.keysym.scancode)->SetDown(true);
					break;

				case SDL_KEYUP:
					if (!console->isOpen)
						inputManager->GetKeyState(event.key.keysym.scancode)->SetDown(false);
					break;

				case SDL_MOUSEBUTTONDOWN:
					if (!console->isOpen)
						inputManager->GetButtonState(event.button.button)->SetDown(true);
					break;

				case SDL_MOUSEBUTTONUP:
					if (!console->isOpen)
						inputManager->GetButtonState(event.button.button)->SetDown(false);
					break;

				case SDL_MOUSEMOTION:
					if (!console->isOpen)
						inputManager->SetMousePos(event.motion.x, event.motion.y);
			}
		}

		performanceProfiler->End();

		performanceProfiler->Begin("input_last_frame_state_update");
		inputManager->UpdateLastFrameStates();
		performanceProfiler->End();

		performanceProfiler->Begin("entity_update");
		entityManager->UpdateEntities();
		performanceProfiler->End();

		PE::CallEventFunction(PE::GAME_UPDATE, PE::EventParameters(0, 0, {0, 0}));
	}

	void Game::Tick()
	{
		entityManager->TickEntities();
	}

	void Game::Draw()
	{
		window->bg_color = { 255, 255, 255, 255 };

		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		window->ClearBackground();

		PE::CallEventFunction(PE::GAME_DRAW, PE::EventParameters(0, 0, { 0, 0 }));


		performanceProfiler->Begin("entity_drawing");
		entityManager->DrawEntities();
		performanceProfiler->End();

		// lightManager->CastLightRay({50, 50}, Utils::Color(255, 255, 255, 255), 1000, 100);

		if (lightingEnabled)
		{
			performanceProfiler->Begin("lighting");

			SDL_Texture* light_map = lightManager->GenerateLightMap();
			SDL_SetTextureBlendMode(light_map, SDL_BLENDMODE_MUL);

			SDL_RenderCopy(window->GetSDLRenderer(), light_map, NULL, NULL);

			performanceProfiler->End();
		}

		Vector old_cam_offset = window->camera_offset;
		window->camera_offset = { 0, 0 };

		if (console->isOpen)
		{
			console->Draw();

			std::map<double, std::string> timings = performanceProfiler->GetTimings();

			unsigned int iter = 1;
			for (auto [key, val] : timings)
			{
				fontManager->DrawString({14, double(14 * iter + 3) }, "default", val + ": " + std::to_string(key), Utils::Color(255, 0, 0, 255));
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
		shouldQuit = true;
	}

	void Game::SetGameName(std::string name)
	{
		gameName = name;
		SDL_SetWindowTitle(window->GetSDLWindow(), name.c_str());
	}

	void Game::SetGameVersion(std::string version)
	{
		gameVersion = version;
	}

	void Game::SetContentPath(std::string path)
	{
		path = "./" + path;

		gameContentPath = path;
	}

	void Game::SetEventHandler(void (*event_handler)(EventType, EventParameters))
	{
		PE::eventHandler = event_handler;
	}

	float Game::GetFrameTime()
	{
		return deltaTime.count();
	}

	void Game::UpdateGameName()
	{
		window->SetTitle(gameName);
	}
}
