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

		class ENGINE_API Label : public Widget
		{
		public:
			Utils::Color fontColor;

			std::string font;
			std::string text;

			Label(Vector position, std::string font, std::string text, Utils::Color fontColor);

			void Draw();
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

			Utils::Color textColor = { 255, 255, 255, 255 };

			Utils::Color normalColor = { 25, 25, 25, 255 };
			Utils::Color hoverColor = { 60, 60, 60, 255 };
			Utils::Color pressedColor = { 125, 125, 125, 255 };

			Button(std::string font, std::string text, Vector position, Vector size, void(*fptr_OnButtonPress)() = nullptr);

			void Draw();
			void Update();

			void OnClick(int button, Vector mousePos);
		};

		class ENGINE_API CheckBox : public Widget
		{
		protected:
			bool isChecked = false;

		public:
			Utils::Color textColor = { 0, 0, 0, 255 };

			Vector size;

			std::string font;
			std::string text;

			Utils::Color currentColor;

			Utils::Color normalColor = { 25, 25, 25, 255 };
			Utils::Color hoverColor = { 60, 60, 60, 255 };
			Utils::Color checkColor = { 255, 255, 255, 255 };

			CheckBox(std::string font, std::string text, Vector position, Vector size);

			void Update();
			void Draw();

			void OnClick(int button, Vector mousePos);


			bool IsChecked();
			void SetChecked(bool checked);
		};
	}
}