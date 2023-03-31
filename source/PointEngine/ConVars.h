#pragma once

#include "Core.h"
#include "Game.h"

#include <string>
#include <unordered_map>

namespace PE
{
	class Game;

	enum ConVarType
	{
		CONVAR_BOOL,
		CONVAR_INT,
		CONVAR_FLOAT,
		CONVAR_STRING
	};

	class ENGINE_API ConVar
	{
		public:
		ConVarType type;
		void* data_pointer;

		ConVar() {}
		ConVar(ConVarType type, void* data_pointer);

		void SetConVar(void* data);
	};

	class ENGINE_API ConVarManager
	{
		private:
		std::unordered_map<std::string, ConVar> con_vars;

		public:
		ConVarManager(PE::Game* game);

		PE::Game* game;

		void RegisterConVar(std::string name, ConVar convar);
		void RemoveConVar(std::string name);
		void SetConVar(std::string name, void* data);
		ConVar* FindConVar(std::string name);
	};
}
