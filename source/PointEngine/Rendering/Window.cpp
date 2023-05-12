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
			// Initialize window - PT
			PE::LogInfo("Initializing window");

			glfwInit();

			window = glfwCreateWindow(800, 600, "PointEngine window", NULL, NULL);
			glfwMakeContextCurrent(window);

			PE::LogInfo("Window size is " + std::to_string(width) + " " + std::to_string(height));


			this->fullscreen = fullscreen;

			this->width = width;
			this->height = height;

			if (window == NULL)
			{
				const char* error;
				glfwGetError(&error);

				LogError(std::string(error));

				PE::CallEventFunction(PE::GAME_CLOSED, PE::EventParameters(0, 2, { 0, 0 }));
				exit(2);
			}

			PE::LogInfo("Initialized Window");

			// Set the window to fullscreen - PT
			if (fullscreen)
			{
				PE::LogInfo("Window fullscreen");
			}
			else
			{
				PE::LogInfo("Window not fullscreen");
			}
		}

		Window::~Window()
		{
		}

		int Window::GetHeight() { return height; }
		int Window::GetWidth() { return width; }
		bool Window::IsFullscreen() { return fullscreen; }

		Vector Window::GetMonitorRes()
		{

			return {0, 0};

		}

		GLFWwindow* Window::GetGLFWWindow() { return window; }
	
		void Window::SwapBuffers()
		{
			glfwSwapBuffers(window);
		}

		void Window::SetSize(Vector size)
		{
			width = size.x;
			height = size.y;

		}

		void Window::SetFullscreen(bool fullscreen)
		{
		}

		void Window::SetTitle(std::string title)
		{
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
