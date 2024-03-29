#pragma once

#include <string>

#include "ConVars.h"
#include "Game.h"

namespace PE
{
	class Game;
	class ConVarManager;

	class ENGINE_API Console
	{
		public:
		Console(PE::Game* game);
		~Console();

		PE::Game* game;

		std::string contents = "";
		char command[255] = "";
		bool isOpen = false;

		ConVarManager* convarManager;

		void RunCommand(std::string cmd);
		void Draw();
		void Clear();
		void Print(std::string str);
	};
}
