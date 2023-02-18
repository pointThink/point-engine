#include "Console.h"

#include "imgui/imgui.h"

#include <iostream>

void PE::Console::RunCommand(std::string commands)
{
}

void PE::Console::Draw()
{
	ImGui::Begin("Console", &is_open);

	// ImGui::SetCursorScreenPos({0, ImGui::GetWindowSize().y - 20});

	bool scroll_down = false;

	ImGui::PushItemWidth(ImGui::GetWindowWidth() - 15);
	if (ImGui::InputText("Enter command", command, 255, ImGuiInputTextFlags_EnterReturnsTrue))
	{
		contents = contents + std::string(command) + '\n';
		strcpy(command, "");

		scroll_down = true;
	}


	ImGui::PopItemWidth();
	ImGui::BeginChild("eeee", {ImGui::GetWindowWidth() - 15, ImGui::GetWindowHeight() - 60}, 2, ImGuiWindowFlags_None);

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
