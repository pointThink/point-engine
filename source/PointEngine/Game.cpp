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
		inputManager = new PE::InputManager;
		// lightManager = new PE::Lighting::LightingManager(5, Vector(window->GetWidth(), window->GetHeight()));
		fontManager = new PE::Font::FontManager;
		performanceProfiler = new PE::Performance::PerformanceProfiler;
		rng = new PE::Random::RNG;

		// load the default font
		fontManager->LoadExternalFont("default", "C:/Windows/Fonts/consola.ttf", 14);

		// initialize the imgui library - PT
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplSDL2_InitForSDLRenderer(window->GetSDLWindow(), window->GetSDLRenderer());
		ImGui_ImplSDLRenderer_Init(window->GetSDLRenderer());

		// imgui style i stole from the internet
		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
		colors[ImGuiCol_Border] = ImVec4(0.39f, 0.39f, 0.39f, 1.0f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
		colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
		colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
		colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_DockingPreview] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
		colors[ImGuiCol_DockingEmptyBg] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TableBorderStrong] = ImVec4(0.39f, 0.39f, 0.39f, 1.0f);
		colors[ImGuiCol_TableBorderLight] = ImVec4(0.39f, 0.39f, 0.39f, 1.0f);
		colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
		colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

		// load a font that dosent suck as much as the default - PT
		io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/verdana.ttf", 16);

		// define some engine convars
		// console->convarManager->RegisterConVar("g_title", ConVar(CONVAR_STRING, &gameName, MethodPointer<PE::Game>(this, &UpdateGameName)));
		console->convarManager->RegisterConVar("g_version", ConVar(CONVAR_STRING, &gameVersion));

		console->convarManager->RegisterConVar("r_bg_color_r", ConVar(CONVAR_INT, &window->bg_color.r));
		console->convarManager->RegisterConVar("r_bg_color_g", ConVar(CONVAR_INT, &window->bg_color.g));
		console->convarManager->RegisterConVar("r_bg_color_b", ConVar(CONVAR_INT, &window->bg_color.b));
		console->convarManager->RegisterConVar("r_lightingEnabled", ConVar(CONVAR_BOOL, &lightingEnabled));

		// default content path
		SetContentPath("content");

		PE::CallEventFunction(PE::GAME_INIT, PE::EventParameters(0, 0, { 0, 0 }));

		initialized = true;

		// lightManager->CreateCellArray({ double(window->GetWidth()), double(window->GetHeight()) }, 5);

		/*
		if (lightingEnabled)
		{
			lightManager->CreateLightSource({ 400, 300 }, { 0, 255, 0, 255 }, 300);
			lightManager->CreateLightSource({ 780, 590 }, { 0, 0, 255, 255 }, 300);
			lightManager->CreateLightSource({ 20, 10 }, { 255, 0, 0, 255 }, 300);
		}
		*/

		//LogInfo(std::to_string(int(window->GetWidth())) + " " + std::to_string(int(window->GetHeight())));

		SetCurrentGameState(new PE::GameState::GameState, false);
	}

	void Game::Run()
	{
		if (!initialized)
		{
			LogError("Engine not initialized properly or not at all, cehck if Game::Init() was ran anywhere or if any errors occured during initialization");
			PE::CallEventFunction(PE::GAME_CLOSED, PE::EventParameters(0, 5, { 0, 0 }));
			exit(5);
		}

		// draw the splash screen
		// i would make a splash game state but i think that would interfere a little bit with the other game states
		spriteManager->LoadSprite("../../../engineRes/Logo.png", "splash");

		Vector splashPos;

		Vector screenSize = { window->GetWidth(), window->GetHeight() };

		// hardcoded splash size - good enough for now
		splashPos = { screenSize.x / 2 - 1123 / 2, screenSize.y / 2 - 420 / 2 };
		Utils::Color oldBgColor = window->bg_color;


		Utils::Timer splashTimer;
		splashTimer.Reset();

		while (!splashTimer.HasTimeElapsed(2))
		{
			window->bg_color = { 32, 32, 32, 255 };

			window->ClearBackground();
			spriteManager->DrawSprite("splash", splashPos);
			window->PresentRenderer();
		}

		spriteManager->RemoveSprite("splash");

		window->bg_color = oldBgColor;

		while (!shouldQuit)
		{
			deltaTime = frameTimer.GetTime();
			frameTimer.Reset();

			Update();

			//performanceProfiler->Begin("tick");
			// check if should tick
			if (tickTimer.HasTimeElapsed(1.0 / ticksPerSecond))
			{
				Tick();
				tickTimer.Reset();
			}

			//performanceProfiler->End();

			Draw();

			performanceProfiler->Clear();
		}

		PE::CallEventFunction(PE::GAME_CLOSED, PE::EventParameters(0, 0, {0, 0}));
        PE::LogInfo("Quitting");


        PE::LogInfo("Deinitializing window");
		delete window;
		PE::LogInfo("Deinitializing sprite manager");
		delete spriteManager;
		PE::LogInfo("Deinitializing input manager");
		delete inputManager;
		PE::LogInfo("Deinitializing font manager");
		delete fontManager;
		PE::LogInfo("Deinitializing rng");
		delete rng;
		
		// delete currentGameState;
		PE::LogInfo("Deinitialized everything");
		PE::LogDeInit();

		delete console;
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
					{
						inputManager->GetButtonState(event.button.button)->SetDown(true);
						currentGameState->uiManager->HandleMouseClick(event.button.button, inputManager->GetMousePos());
					}	
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

		if (!isPaused)
		{
			performanceProfiler->End();

			performanceProfiler->Begin("input_last_frame_state_update");
			inputManager->UpdateLastFrameStates();
			performanceProfiler->End();

			performanceProfiler->Begin("entity_update");
			currentGameState->entityManager->UpdateEntities();
			performanceProfiler->End();

		}

		PE::CallEventFunction(PE::GAME_UPDATE, PE::EventParameters(0, 0, {0, 0}));

		currentGameState->OnUpdate();
	}

	void Game::Tick()
	{
		//LogInfo("Ticking");

		if (!isPaused)
			currentGameState->entityManager->TickEntities();

		currentGameState->OnTick();

		currentGameState->uiManager->UpdateUI();
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
		currentGameState->entityManager->DrawEntities();
		performanceProfiler->End();

		// lightManager->CastLightRay({50, 50}, Utils::Color(255, 255, 255, 255), 1000, 100);

		if (lightingEnabled)
		{
			performanceProfiler->Begin("lighting");

			//SDL_Texture* light_map = lightManager->GenerateLightMap();
			//SDL_SetTextureBlendMode(light_map, SDL_BLENDMODE_MUL);

			//SDL_RenderCopy(window->GetSDLRenderer(), light_map, NULL, NULL);

			performanceProfiler->End();
		}

		Vector old_cam_offset = window->camera_offset;
		window->camera_offset = { 0, 0 };

		currentGameState->OnDraw();

		currentGameState->uiManager->DrawUI();

		if (console->isOpen)
		{
			console->Draw();

			std::map<double, std::string> timings = performanceProfiler->GetTimings();

			unsigned int iter = 1;


			// Draw Performance window
			ImGui::Begin("Performance");

			ImGui::Text(("Frames per second - " + std::to_string(1 / GetFrameTime())).c_str());
			ImGui::Text("");

			ImGui::Text(("Entity count - " + std::to_string(currentGameState->entityManager->GetEntityCount())).c_str());
			ImGui::Text("");


			for (auto [key, val] : timings)
			{

				ImGui::Text((val + ": " + std::to_string(key)).c_str());
				iter++;
			}

			ImGui::End();
		}

		window->camera_offset = old_cam_offset;

		ImGui::Render();
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());

		window->PresentRenderer();
	}


	void Game::SetCurrentGameState(GameState::GameState* state, bool deleteOld)
	{
		// remove the old state
		if (currentGameState != nullptr && deleteOld)
		{
			currentGameState->DeInit();
			delete currentGameState;
		}

		currentGameState = state;
		state->Init();
	}

	GameState::GameState* Game::GetCurrentGameState()
	{
		return currentGameState;
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
