#include "UI/Widgets.h"

#include "Logging.h"

using namespace PE::UI;

void Widget::SetTag(std::string tag)
{
	this->tag = tag;
}

Label::Label(Vector position, std::string font, std::string text, Utils::Color fontColor)
{
	this->position = position;
	this->font = font;
	this->text = text;
	this->fontColor = fontColor;
}

void Label::Draw()
{
	PE_GAME->fontManager->DrawString(position, font, text, fontColor);
}


Button::Button(std::string font, std::string text, Vector position, Vector size, void (*fptr_OnButtonPress)())
{
	this->font = font;
	this->text = text;

	this->position = position;
	this->size = size;

	this->fptr_OnButtonPress = fptr_OnButtonPress;

	currentColor = normalColor;
}

void Button::OnClick(int button, Vector position)
{
	if ((position.x >= this->position.x && position.y >= this->position.y) && (position.x <= this->position.x + this->size.x && position.y <= this->position.y + this->size.y))
	{
		if (fptr_OnButtonPress != nullptr)
			fptr_OnButtonPress();

		currentColor = pressedColor;
		pressHighlightTimer.Reset();
	}
}

void Button::Draw()
{
	//LogInfo("Drawing");
	PE_GAME->window->DrawSquare(position, size, currentColor);

	// draw the text
	Vector drawPos = position;
	drawPos.x = drawPos.x + ( size.x /2 ) - ( PE_GAME->fontManager->GetStringLength(font, text) / 2 );
	drawPos.y = drawPos.y + (size.y / 2) - (PE_GAME->fontManager->GetStringHeight(font, text) / 2);

	PE_GAME->fontManager->DrawString(drawPos, font, text, { 255, 255, 255, 255 });
}

void Button::Update()
{
	Vector mousePos = PE_GAME->inputManager->GetMousePos();

	if (pressHighlightTimer.HasTimeElapsed(postPressHighlightTime))
	{
		if ((mousePos.x >= this->position.x && mousePos.y >= this->position.y) && (mousePos.x <= this->position.x + this->size.x && mousePos.y <= this->position.y + this->size.y))
			currentColor = hoverColor;
		else
			currentColor = normalColor;
	}
}


CheckBox::CheckBox(std::string font, std::string text, Vector position, Vector size)
{
	this->font = font;
	this->text = text;

	this->position = position;
	this->size = size;

	currentColor = normalColor;
}

void CheckBox::Draw()
{
	PE_GAME->window->DrawSquare(position, size, currentColor);

	if (isChecked)
	{
		Vector smallerRectPos = position;
		Vector smallerRectSize = size;

		smallerRectSize.x = size.x * 0.5;
		smallerRectSize.y = size.y * 0.5;

		smallerRectPos.x = position.x + (size.x / 4);
		smallerRectPos.y = position.y + (size.y / 4);

		PE_GAME->window->DrawSquare(smallerRectPos, smallerRectSize, checkColor);
	}

	// draw the checkbox text
	Vector textPos;

	textPos.x = position.x + size.x + 7;
	textPos.y = position.y + size.y / 2 - PE_GAME->fontManager->GetStringHeight(font, text) / 2;

	PE_GAME->fontManager->DrawString(textPos, font, text, textColor);
}

void CheckBox::Update()
{
	Vector mousePos = PE_GAME->inputManager->GetMousePos();

	if ((mousePos.x >= this->position.x && mousePos.y >= this->position.y) && (mousePos.x <= this->position.x + this->size.x && mousePos.y <= this->position.y + this->size.y))
		currentColor = hoverColor;
	else
		currentColor = normalColor;
}

void CheckBox::OnClick(int button, Vector position)
{
	if ((position.x >= this->position.x && position.y >= this->position.y) && (position.x <= this->position.x + this->size.x && position.y <= this->position.y + this->size.y))
	{
		//LogInfo("Check!");
		isChecked = !isChecked;
		//currentColor = pressedColor;
		//pressHighlightTimer.Reset();
	}
}

bool CheckBox::IsChecked()
{
	return isChecked;
}

void CheckBox::SetChecked(bool checked)
{
	isChecked = checked;
}