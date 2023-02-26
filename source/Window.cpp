#include "Window.h"

#include <SDL2\SDL_image.h>

#include "Logging.h"
#include "Event.h"

PE::Rendering::Window::Window(std::string title, int width, int height, bool fullscreen)
{
	// Initialize SDL2 - PT
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		PE::LogError("Error initializing SDL2: " + std::string(SDL_GetError()));
		PE::CallEventFunction(PE::GAME_CLOSED, PE::EventParameters(0, 1, {0, 0}));
		exit(1);
	}

	PE::LogInfo("SDL Initialized");

	// Initialize window - PT
	PE::LogInfo("Initializing window");
	PE::LogInfo("Window size is " + std::to_string(width) + " " + std::to_string(height));

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_ALLOW_HIGHDPI);

	this->fullscreen = fullscreen;

	this->width = width;
	this->height = height;

	if (window == NULL)
	{
		PE::LogError("Error initializing window: " + std::string(SDL_GetError()));
		PE::CallEventFunction(PE::GAME_CLOSED, PE::EventParameters(0, 2, {0, 0}));
		exit(2);
	}

	PE::LogInfo("Initialized Window");

	// Set the window to fullscreen - PT
	if (fullscreen)
	{
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		PE::LogInfo("Window fullscreen");
	}
	else
	{
		PE::LogInfo("Window not fullscreen");
	}


	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	if (renderer == NULL)
	{
		PE::LogError("Error initializing renderer: " + std::string(SDL_GetError()));
		PE::CallEventFunction(PE::GAME_CLOSED, PE::EventParameters(0, 3, {0, 0}));
		exit(3);
	}

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	PE::LogInfo("Set renderer color");

	// Initialize the SDL_Image library - PT
	if (!(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)))
	{
		PE::LogError("Error initializing the SDL Image library " + std::string(IMG_GetError()));
		PE::CallEventFunction(PE::GAME_CLOSED, PE::EventParameters(0, 4, {0, 0}));
		exit(4);
	}

	PE::LogInfo("SDL Image initialized");

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

PE::Rendering::Window::~Window()
{

	// note for the future
	// remember to destroy the renderer before you destroy the window - PT
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

int PE::Rendering::Window::GetHeight() {return height;}
int PE::Rendering::Window::GetWidth() {return width;}
bool PE::Rendering::Window::IsFullscreen() {return fullscreen;}

SDL_Window * PE::Rendering::Window::GetSDLWindow() {return window;}
SDL_Renderer * PE::Rendering::Window::GetSDLRenderer() {return renderer;}

void PE::Rendering::Window::SetSize(int x, int y)
{
	SDL_SetWindowSize(window, x, y);
}

void PE::Rendering::Window::SetFullscreen(bool fullscreen)
{
	if (fullscreen)
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	else
		SDL_SetWindowBordered(window, SDL_TRUE);
}

void PE::Rendering::Window::ClearBackground()
{
	SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
	SDL_RenderClear(renderer);
}

void PE::Rendering::Window::PresentRenderer()
{
	SDL_RenderPresent(renderer);
}

void PE::Rendering::Window::SetTitle(std::string title)
{
	SDL_SetWindowTitle(window, title.c_str());
}

void PE::Rendering::Window::DrawSquare(Vector pos, Vector size, Utils::Color color)
{
	SDL_Rect rect;

	rect.x = pos.x;
	rect.y = pos.y;
	rect.w = size.x;
	rect.h = size.y;

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
}


void PE::Rendering::Window::DrawCircle(Vector pos, float radius, Utils::Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	// draw a fugnkin circle using the midpoint circle algorithm - PT
	int x = radius - 1;
	int y = 0;

	int midpoint = 1 - radius;

	while (x > y)
	{
		y++;

		// check if midpoint is inside the perimiter - PT
		if (midpoint >= 0)
			midpoint = midpoint + 2*y + 1;
		else
		{
			x--;
			midpoint = midpoint + 2*y - 2*x + 1;
		}

		if (x > y) // if this condition is true that means that all points have been drawn - PT
			break;

		// Draw the generated points - PT
		SDL_RenderDrawPoint(renderer, x + pos.x, y + pos.y);
		SDL_RenderDrawPoint(renderer, -x + pos.x, y + pos.y);
		SDL_RenderDrawPoint(renderer, x + pos.x, -y + pos.y);
		SDL_RenderDrawPoint(renderer, -x + pos.x, -y + pos.y);

		if (x != y)
		{
			SDL_RenderDrawPoint(renderer, y + pos.x, x + pos.y);
			SDL_RenderDrawPoint(renderer, -y + pos.x, x + pos.y);
			SDL_RenderDrawPoint(renderer, y + pos.x, -x + pos.y);
			SDL_RenderDrawPoint(renderer, -y + pos.x, -x + pos.y);
		}
	}

	SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
}
