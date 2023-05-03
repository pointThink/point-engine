#include "Window.h"

#include <SDL_image.h>

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


			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

			if (renderer == NULL)
			{
				PE::LogError("Error initializing renderer: " + std::string(SDL_GetError()));
				PE::CallEventFunction(PE::GAME_CLOSED, PE::EventParameters(0, 3, { 0, 0 }));
				exit(3);
			}

			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			PE::LogInfo("Set renderer color");

			// Initialize the SDL_Image library - PT
			if (!(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)))
			{
				PE::LogError("Error initializing the SDL Image library " + std::string(IMG_GetError()));
				PE::CallEventFunction(PE::GAME_CLOSED, PE::EventParameters(0, 4, { 0, 0 }));
				exit(4);
			}

			PE::LogInfo("SDL Image initialized");

			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		}

		Window::~Window()
		{

			// note for the future
			// remember to destroy the renderer before you destroy the window - PT
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
		}

		int Window::GetHeight() { return height; }
		int Window::GetWidth() { return width; }
		bool Window::IsFullscreen() { return fullscreen; }

		SDL_Window* Window::GetSDLWindow() { return window; }
		SDL_Renderer* Window::GetSDLRenderer() { return renderer; }

		void Window::SetSize(int x, int y)
		{
			width = x;
			height = y;

			SDL_SetWindowSize(window, x, y);
		}

		void Window::SetFullscreen(bool fullscreen)
		{
			if (fullscreen)
				SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
			else
				SDL_SetWindowBordered(window, SDL_TRUE);
		}

		void Window::ClearBackground()
		{
			SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
			SDL_RenderClear(renderer);
		}

		void Window::PresentRenderer()
		{
			SDL_RenderPresent(renderer);
		}

		void Window::SetTitle(std::string title)
		{
			SDL_SetWindowTitle(window, title.c_str());
		}

		void Window::DrawSquare(Vector pos, Vector size, Utils::Color color)
		{
			SDL_Rect rect;

			rect.x = int(pos.x) + int(camera_offset.x);
			rect.y = int(pos.y) + int(camera_offset.y);
			rect.w = int(size.x);
			rect.h = int(size.y);

			// check if the square should be drawn
			// check if square is within bounderies of the max draw
			if (ShouldDraw(pos, size))
			{
				SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
				SDL_RenderFillRect(renderer, &rect);
				SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
			}
			else
			{
				// PE::LogInfo("Square out of bounds");
			}
		}


		void Window::DrawCircle(Vector pos, float radius, Utils::Color color)
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
					midpoint = midpoint + 2 * y + 1;
				else
				{
					x--;
					midpoint = midpoint + 2 * y - 2 * x + 1;
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