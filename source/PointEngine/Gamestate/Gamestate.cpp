#include "Gamestate/Gamestate.h"
#include "Game.h"

using namespace PE::GameState;


GameState::GameState()
{
	entityManager = new Entity::EntityManager(PE_GAME);
	uiManager = new UI::UIManager;
}

GameState::~GameState()
{
	delete entityManager;
	delete uiManager;
}