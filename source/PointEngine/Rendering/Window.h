#pragma once

#include <string>

#include "SDL.h"
#include "Vector.h"
#include "Utils/Utils.h"

namespace PE
{
	namespace Rendering
	{
		class ENGINE_API Window
		{
			private:
			SDL_Window* window = NULL;

			// Window with and height is currently placeholder value
			// These values should be set in the game settings or something - PT
			int width;
			int height;

			bool fullscreen = 0;

			public:
			Vector camera_offset = {0, 0};

			Utils::Color bg_color;

			Window(std::string title, int width, int heigh, bool fullscreen);
			~Window();

			// Getters setters and stuff - PT
			int GetWidth();
			int GetHeight();
			bool IsFullscreen();

			Vector GetMonitorRes();

			SDL_Window* GetSDLWindow();
			
			void SetSize(Vector size);
			void SetFullscreen(bool fullscreen);
			void SetTitle(std::string title);

			// check if a an object is out of range and if it should be draw
			bool ShouldDraw(Vector pos, Vector size);
		};
	};
};
