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
			// These values should be set in the game settings or something
			int width;
			int height;

			bool fullscreen = 0;

			public:
			Window(std::string title, int width, int heigh, bool fullscreen);
			~Window();


			// Getters setters and stuff
			int GetWidth();
			int GetHeight();
			bool IsFullscreen();

			void SetSize(int x, int y);
			void SetFullscreen(bool fullscreen);
		};
	};
};
