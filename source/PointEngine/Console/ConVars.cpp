#include "ConVars.h"

#include "Logging.h"
#include <iostream>

namespace PE
{
	ConVar::ConVar(ConVarType type, void* data_pointer)
	{
		this->type = type;
		this->dataPointer = data_pointer;
	}

	ConVarManager::ConVarManager(Game* game)
	{
		this->game = game;
	}

	void ConVarManager::RegisterConVar(std::string name, ConVar convar)
	{
		conVars.insert({ name, convar });
	}

	void ConVarManager::RemoveConVar(std::string name)
	{
		conVars.erase(conVars.find(name));
	}

	void ConVarManager::SetConVar(std::string name, void* data)
	{

		ConVar cv = conVars.find(name)->second;

		// welcome to hell - PT
		if (cv.type == CONVAR_BOOL)
			*(bool*)(cv.dataPointer) = *(bool*)data;
		else if (cv.type == CONVAR_INT)
			*(int*)(cv.dataPointer) = *(int*)data;
		else if (cv.type == CONVAR_FLOAT)
			*(float*)(cv.dataPointer) = *(float*)data;
		else if (cv.type == CONVAR_STRING)
			*(std::string*)(cv.dataPointer) = *(std::string*)data;
	}

	ConVar* ConVarManager::FindConVar(std::string name)
	{
		if (!conVars.contains(name))
		{
			LogWarning("Could not find console variable");
			return NULL;
		}

		return &conVars.find(name)->second;
	}

}
