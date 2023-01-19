#pragma once

#include "SDL2\SDL.h"

class Window
{
	private:
	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;
	SDL_Texture * renderer_texture = NULL;

	// Window with and height is currently placeholder value
	// These values should be set in the game settings or something
	int width;
	int height;

	bool fullscreen = 0;

	public:
	Window();
	~Window();

	int GetWidth();
	int GetHeight();
};