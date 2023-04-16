#pragma once

#include <vector>

#include "Core.h"
#include "UI/Widgets.h"

namespace PE
{
	namespace UI
	{
		class ENGINE_API UIManager
		{
			std::vector<Widget*> widgets;

		public:
			void DrawUI();
			void UpdateUI();

			void HandleKeyPress(int code, char character);
			void HandleMouseClick(int button, Vector position);

			void AddWidget(std::string tag, Widget* widget);
			void RemoveWidget(std::string tag);

			void ClearWidgets();
		};
	}
}
