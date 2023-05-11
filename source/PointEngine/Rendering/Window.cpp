#include "Window.h"

//#include <SDL_image.h>

#include "Logging.h"
#include "Event.h"

namespace PE
{
	namespace Rendering
	{
		Window::Window(std::string title, int width, int height, bool fullscreen)
		{
			// Initialize SDL2 - PT
			if (SDL_Init(SDL_INIT_VIDEO))
			{
				PE::LogError("Error initializing SDL2: " + std::string(SDL_GetError()));
				PE::CallEventFunction(PE::GAME_CLOSED, PE::EventParameters(0, 1, { 0, 0 }));
				exit(1);
			}

			PE::LogInfo("SDL Initialized");

			// Initialize window - PT
			PE::LogInfo("Initializing window");
			PE::LogInfo("Window size is " + std::to_string(width) + " " + std::to_string(height));

			window = SDL_CreateWindow(title.c_str(), 30, 50, width, height, SDL_WINDOW_ALLOW_HIGHDPI);

			this->fullscreen = fullscreen;

			this->width = width;
			this->height = height;

			if (window == NULL)
			{
				PE::LogError("Error initializing window: " + std::string(SDL_GetError()));
				PE::CallEventFunction(PE::GAME_CLOSED, PE::EventParameters(0, 2, { 0, 0 }));
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
		}

		Window::~Window()
		{
			SDL_DestroyWindow(window);
		}

		int Window::GetHeight() { return height; }
		int Window::GetWidth() { return width; }
		bool Window::IsFullscreen() { return fullscreen; }

		Vector Window::GetMonitorRes()
		{
			SDL_DisplayMode mode;

			SDL_GetCurrentDisplayMode(0, &mode);

			return { double(mode.w), double(mode.h) };
		}

		SDL_Window* Window::GetSDLWindow() { return window; }
		
		void Window::SetSize(Vector size)
		{
			width = size.x;
			height = size.y;

			SDL_SetWindowSize(window, size.x, size.y);
		}

		void Window::SetFullscreen(bool fullscreen)
		{
			if (fullscreen)
				SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
			else
				SDL_SetWindowBordered(window, SDL_TRUE);
		}

		void Window::SetTitle(std::string title)
		{
			SDL_SetWindowTitle(window, title.c_str());
		}

		bool Window::ShouldDraw(Vector pos, Vector size)
		{
			Vector minDraw;
			minDraw.x = 0 - (size.x * 2) - camera_offset.x;
			minDraw.y = 0 - (size.y * 2) - camera_offset.y;

			Vector maxDraw;
			maxDraw.x = width + (size.x * 2);
			maxDraw.y = height + (size.y * 2);

			// check if object is located within minDraw and maxDraw
			if ((pos.x >= minDraw.x && pos.x <= minDraw.x + maxDraw.x) && (pos.y >= minDraw.y && pos.y <= minDraw.y + maxDraw.y))
			{
				return true;
			}

			return false;
		}
	}
}