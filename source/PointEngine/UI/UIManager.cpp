#include "UI/UIManager.h"

using namespace PE::UI;

void UIManager::DrawUI()
{
	for (Widget* widget : widgets)
	{
		widget->Draw();
	}
}

void UIManager::UpdateUI()
{
	for (Widget* widget : widgets)
	{
		widget->Update();
	}
}


void UIManager::HandleMouseClick(int button, Vector position)
{
	for (Widget* widget : widgets)
	{
		widget->OnClick(button, position);
	}
}

void UIManager::HandleKeyPress(int code, char character)
{
	for (Widget* widget : widgets)
	{
		widget->OnKeyPress(code, character);
	}
}


void UIManager::AddWidget(std::string tag, Widget* widget)
{
	widget->SetTag(tag);
	widgets.push_back(widget);
}