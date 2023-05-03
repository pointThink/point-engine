#include "UI/UIManager.h"

namespace PE
{
	namespace UI
	{
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

		void UIManager::RemoveWidget(std::string tag)
		{
			for (auto it = widgets.begin(); it != widgets.end();)
			{
				if ((*it)->GetTag() == tag)
				{
					widgets.erase(it);
				}
				else
				{
					it++;
				}
			}
		}

		void UIManager::ClearWidgets()
		{
			for (Widget* widget : widgets)
			{
				delete widget;
			}

			widgets.clear();
		}
	}
}
