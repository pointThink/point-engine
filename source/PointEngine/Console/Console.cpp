#define _CRT_SECURE_NO_WARNINGS

#include "Console.h"

#include "imgui.h"
#include "Utils/Utils.h"
#include "Logging.h"

#include <iostream>
#include <string>
#include <cstring>

namespace PE
{
	Console::Console(Game* game)
	{
		this->game = game;
		convarManager = new ConVarManager(game);
	}

	Console::~Console()
	{
		delete convarManager;
	}

	void Console::RunCommand(std::string command)
	{
		// split the command into arguments
		bool inQuotes = false;
		std::string wipString = "";

		for (int i = 0; i <= command.size(); i++)
		{
			if (command.c_str()[i] == ' ' && !inQuotes)
				wipString = wipString + "\n";
			else if (command[i] == '"')
				inQuotes = !inQuotes;
			else
				wipString = wipString + command[i];
		}

		std::vector<std::string> args = Utils::SplitString(wipString, "\n");

		if (args[0] == "clear")
		{
			Clear();
		}
		else
		{
			ConVar* convar = convarManager->FindConVar(args[0]);

			if (convar != NULL)
			{
				switch (convar->type)
				{
				case CONVAR_BOOL:
				{
					bool value = Utils::StringToBool(args[1]); // the value needs to be set as a variable first otherwise it will throw an error - PT
					convarManager->SetConVar(args[0], &value);
					break;
				}

				case CONVAR_INT:
				{
					int value = std::stoi(args[1]);
					convarManager->SetConVar(args[0], &value);
					break;
				}

				case CONVAR_FLOAT:
				{
					float value = std::stof(args[1]);
					convarManager->SetConVar(args[0], &value);
					break;
				}

				case CONVAR_STRING:
					convarManager->SetConVar(args[0], &args[1]);
					break;
				}
			}
			else
			{
				LogWarning("Could not change convar " + args[0] + " because it does not exist");
			}
		}
	}

	void Console::Draw()
	{
		ImGui::Begin("Console", &isOpen);

		// ImGui::SetCursorScreenPos({0, ImGui::GetWindowSize().y - 20});

		bool scrollDown = false;

		//ImGui::PushItemWidth(ImGui::GetWindowWidth() - 15);
		if (ImGui::InputText("Enter command", command, 255, ImGuiInputTextFlags_EnterReturnsTrue))
		{
			contents = contents + "> " + std::string(command) + '\n';
			RunCommand(std::string(command));

			strcpy(command, "");

			scrollDown = true;
		}


		//ImGui::PopItemWidth();
		ImGui::BeginChild("text", { ImGui::GetWindowWidth() - 15, ImGui::GetWindowHeight() - 60 }, 2, ImGuiWindowFlags_None);

		ImGui::Text(contents.c_str());

		if (scrollDown)
		{
			ImGui::SetScrollY(ImGui::GetScrollMaxY());
		}


		ImGui::EndChild();
		ImGui::End();
	}

	void Console::Clear()
	{
		contents = "";
	}

	void Console::Print(std::string str)
	{
		contents = contents + str;
	}

}
