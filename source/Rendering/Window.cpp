#include "Window.h"

#include "Logging.h"

PE::Rendering::Window::Window(std::string title, int width, int height, bool fullscreen)
{	// Initialize window
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_ALLOW_HIGHDPI);

	PE::LogInfo("Window size is " + std::to_string(width) + " " + std::to_string(height));

	this->fullscreen = fullscreen;

	this->width = width;
	this->height = height;

	if (window == NULL)
	{
		PE::LogError("Error initializing window: " + std::string(SDL_GetError()));
		exit(1);
	}

	// Set the window to fullscreen
	if (fullscreen)
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
	{
		PE::LogError("Error initializing renderer: " + std::string(SDL_GetError()));
		exit(2);
	}

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

PE::Rendering::Window::~Window()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	delete window;
	delete renderer;
}

int PE::Rendering::Window::GetHeight() {return height;}
int PE::Rendering::Window::GetWidth() {return width;}
bool PE::Rendering::Window::IsFullscreen() {return fullscreen;}

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