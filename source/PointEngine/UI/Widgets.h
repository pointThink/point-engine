#pragma once

#include <iostream>
#include <string>

#include "Core.h"
#include "Vector.h"
#include "Utils/Utils.h"

namespace PE
{
	namespace UI
	{
		class ENGINE_API Widget
		{
		protected:
			std::string tag;
			Vector position;

		public:
			void SetTag(std::string tag);

			virtual void Draw() { std::cout << "Drawing\n"; }
			virtual void Update() {}

			virtual void OnClick(int button, Vector mousePos) {}
			virtual void OnKeyPress(int keyCode, char character) {}
		};

		class ENGINE_API Button : public Widget
		{
		public:
			std::string text;
			std::string font;

			Vector size = { 200, 100 };

			Utils::Timer pressHighlightTimer;
			float postPressHighlightTime = 0.25;

			void (*fptr_OnButtonPress)();

			Utils::Color currentColor;

			Utils::Color normalColor = { 25, 25, 25, 255 };
			Utils::Color hoverColor = { 60, 60, 60, 255 };
			Utils::Color pressedColor = { 125, 125, 125, 255 };

			Button(std::string font, std::string text, Vector position, Vector size, void(*fptr_OnButtonPress)() = nullptr);

			void Draw();
			void Update();

			void OnClick(int button, Vector mousePos);
		};
	}
}