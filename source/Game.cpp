#include "Game.h"
#include "SDL2\SDL.h"

void Game::Run()
{
	SDL_Window * window = NULL;
	SDL_Surface * screenSurface = NULL;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 100, 100, SDL_WINDOW_SHOWN );
	screenSurface = SDL_GetWindowSurface( window );

	//Fill the surface white
	SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
            
	//Update the surface
	SDL_UpdateWindowSurface( window );

	//Hack to get window to stay up
	SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
}

void Game::Update()
{

}

void Game::Draw()
{

}