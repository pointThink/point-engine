#include "ConVars.h"

PE::ConVar::ConVar(ConVarType type, void * data_pointer, void(*on_change))
{
	this->type = type;
	this->data_pointer = data_pointer;
	this->on_change = on_change;
}



void PE::ConVarManager::RegisterConVar(std::string name, ConVar convar)
{
	convars[name] = convar;
}

void PE::ConVarManager::RemoveConVar(std::string name)
{
	convars.erase(convars.find(name));
}

void PE::ConVarManager::SetConVar(std::string name, void * data)
{
	convars.find(name)->second.data_pointer = data;
}