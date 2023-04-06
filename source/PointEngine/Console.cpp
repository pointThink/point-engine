#define _CRT_SECURE_NO_WARNINGS

#include "Console.h"

#include "imgui.h"
#include "Utils.h"
#include "Logging.h"

#include <iostream>
#include <string>
#include <cstring>

PE::Console::Console(PE::Game* game)
{
	this->game = game;
	convar_manager = new PE::ConVarManager(game);
}

PE::Console::~Console()
{
	delete convar_manager;
}

void PE::Console::RunCommand(std::string command)
{
	// split the command into arguments
	bool in_quotes = false;
	std::string wip_string = "";

	for (int i = 0; i <= command.size(); i++)
	{
		if (command.c_str()[i] == ' ' && !in_quotes)
			wip_string = wip_string + "\n";
		else if (command[i] == '"')
			in_quotes = !in_quotes;
		else
			wip_string = wip_string + command[i];
	}

	std::vector<std::string> args = PE::Utils::SplitString(wip_string, "\n");

	if (args[0] == "clear")
	{
		Clear();
	}
	else
	{
		ConVar* convar = convar_manager->FindConVar(args[0]);

		if (convar != NULL)
		{
			switch (convar->type)
			{
				case CONVAR_BOOL:
				{
					bool value = PE::Utils::StringToBool(args[1]); // the value needs to be set as a variable first otherwise it will throw an error - PT
					convar_manager->SetConVar(args[0], &value);
					break;
				}

				case CONVAR_INT:
				{
					int value = std::stoi(args[1]);
					convar_manager->SetConVar(args[0], &value);
					break;
				}

				case CONVAR_FLOAT:
				{
					float value = std::stof(args[1]);
					convar_manager->SetConVar(args[0], &value);
					break;
				}

				case CONVAR_STRING:
					convar_manager->SetConVar(args[0], &args[1]);
					break;
			}
		}
		else
		{
			PE::LogWarning("Could not change convar " + args[0] + " because it does not exist");
		}
	}
}

void PE::Console::Draw()
{
	ImGui::Begin("Console", &is_open);

	// ImGui::SetCursorScreenPos({0, ImGui::GetWindowSize().y - 20});

	bool scroll_down = false;

	//ImGui::PushItemWidth(ImGui::GetWindowWidth() - 15);
	if (ImGui::InputText("Enter command", command, 255, ImGuiInputTextFlags_EnterReturnsTrue))
	{
		contents = contents + "> " + std::string(command) + '\n';
		RunCommand(std::string(command));

		strcpy(command, "");

		scroll_down = true;
	}


	//ImGui::PopItemWidth();
	ImGui::BeginChild("text", {ImGui::GetWindowWidth() - 15, ImGui::GetWindowHeight() - 60}, 2, ImGuiWindowFlags_None);

	ImGui::Text(contents.c_str());

	if (scroll_down)
	{
		ImGui::SetScrollY(ImGui::GetScrollMaxY());
	}


	ImGui::EndChild();
	ImGui::End();
}

void PE::Console::Clear()
{
	contents = "";
}

void PE::Console::Print(std::string str)
{
	contents = contents + str;
}
