#include "ConVars.h"

#include "Logging.h"
#include <iostream>

PE::ConVar::ConVar(ConVarType type, void * data_pointer)
{
	this->type = type;
	this->data_pointer = data_pointer;
	this->on_change = nullptr;
}


PE::ConVar::ConVar(ConVarType type, void * data_pointer, void(*on_change)())
{
	this->type = type;
	this->data_pointer = data_pointer;
	this->on_change = on_change;
}

void PE::ConVarManager::RegisterConVar(std::string name, ConVar convar)
{
	con_vars.insert({name, convar});
}

void PE::ConVarManager::RemoveConVar(std::string name)
{
	con_vars.erase(con_vars.find(name));
}

void PE::ConVarManager::SetConVar(std::string name, void * data)
{

	ConVar cv = con_vars.find(name)->second;

	// welcome to hell - PT
	if (cv.type == CONVAR_BOOL)
		*(bool *)(cv.data_pointer) = *(bool *)data;
	else if (cv.type == CONVAR_INT)
		*(int *)(cv.data_pointer) = *(int *)data;
	else if (cv.type == CONVAR_FLOAT)
		*(float *)(cv.data_pointer) = *(float *)data;
	else if (cv.type == CONVAR_STRING)
		*(std::string *)(cv.data_pointer) = *(std::string *)data;

	if (con_vars.find(name)->second.on_change != nullptr)
	{
		con_vars.find(name)->second.on_change();
	}
}

PE::ConVar * PE::ConVarManager::FindConVar(std::string name)
{
	if (!con_vars.contains(name))
	{
		PE::LogWarning("Could not find console variable");
		return NULL;
	}

	return &con_vars.find(name)->second;
}
