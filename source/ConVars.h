#pragma once

#include "Core.h"

#include <string>
#include <unordered_map>

namespace PE
{
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
		void * data_pointer;
		void (*on_change);

		ConVar() {}
		ConVar(ConVarType type, void * data_pointer, void (*on_change));
	};

	class ENGINE_API ConVarManager
	{
		std::unordered_map<std::string, ConVar> convars;

		void RegisterConVar(std::string name, ConVar convar);
		void RemoveConVar(std::string name);
		void SetConVar(std::string name, void * data);
	};
}