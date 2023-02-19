#pragma once

#include <string>

#include "SDL2\SDL.h"
#include "Vector.h"
#include "Utils.h"

namespace PE
{
	namespace Rendering
	{
		class ENGINE_API Window
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
			Utils::Color bg_color;

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

			void ClearBackground();
			void PresentRenderer();

			void DrawSquare(Vector pos, Vector size, Utils::Color color);
			void DrawCircle(Vector pos, float radius, Utils::Color color);
			//void DrawSquareRound(Vector pos, Vector size, float roundness, Utils::Color color);
			//void DrawTriangle(Vector pos1, Vector pos2, Vector pos3, Utils::Color color)
		};
	};
};
