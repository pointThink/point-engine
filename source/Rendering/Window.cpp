#include "Window.h"

Window::Window(std::string tilte, int width, int heigh)
{	// Initialize window
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	
	this->width = width;
	this->height = height;

	if (window == NULL)
	{
		
	}
}

Window::~Window()
{

}

int Window::GetHeight() {return height;}
int Window::GetWidth() {return width;}