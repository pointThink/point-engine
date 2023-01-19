#include "Game.h"
#include "SDL2\SDL.h"

void Game::Run()
{
	logger = new Logger("log.txt");					// Shameless plug
	logger->LogInfo(game_name + " " + game_version + " running on PointEngine version " + PE_VERSION);
}

void Game::Update()
{

}

void Game::Draw()
{

}