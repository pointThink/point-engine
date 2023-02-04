#pragma once

#include <string>

#include "SDL2\SDL.h"

namespace PE
{
	namespace Rendering
	{
		class Window
		{
			private:
			SDL_Window * window = NULL;
			SDL_Renderer * renderer = NULL;

			// Window with and height is currently placeholder value
			// These values should be set in the game settings or something - PT
			int width;
			int height;

			bool fullscreen = 0;

			public:
			Window(std::string title, int width, int heigh, bool fullscreen);
			~Window();

			// Getters setters and stuff - PT
			int GetWidth();
			int GetHeight();
			bool IsFullscreen();

			SDL_Window * GetSDLWindow();
			SDL_Renderer * GetSDLRenderer();

			void SetSize(int x, int y);
			void SetFullscreen(bool fullscreen);
		};
	};
};
