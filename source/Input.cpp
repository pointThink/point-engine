#include "Input.h"

#include "Logging.h"

void PE::InputManager::SetKeyState(int key, bool is_down)
{
	key_states[key] = is_down;
}

bool PE::InputManager::IsKeyDown(int key)
{
	return key_states[key];
}

void PE::InputManager::SetButtonState(int button, bool is_down)
{
	button_states[button] = is_down;
}

bool PE::InputManager::IsButtonDown(int button)
{
	return button_states[button];
}

void PE::InputManager::SetState(std::string name, bool is_down)
{
	Input input = bindings[name];

	if (input.type == INPUT_MOUSE)
	{
		SetButtonState(input.code, is_down);
		return;
	}
	else if (input.type == INPUT_KEYBOARD)
	{
		SetKeyState(input.code, is_down);
		return;
	}

	PE::LogWarning("Could not find key in bindings: " + name);
}

bool PE::InputManager::IsDown(std::string name)
{
	PE::Input input = bindings[name];

	if (input.type == PE::INPUT_MOUSE)
		return IsButtonDown(input.code);
	if (input.type == PE::INPUT_KEYBOARD)
		return IsKeyDown(input.code);

	PE::LogWarning("Could not find key in bindings: " + name);
	return false;
}

void PE::InputManager::BindKey(std::string name, int key)
{
	bindings[name] = {key, PE::INPUT_KEYBOARD};
}

void PE::InputManager::BindButton(std::string name, int button)
{
	bindings[name] = {button, PE::INPUT_MOUSE};
}

void PE::InputManager::SetMousePos(int x, int y)
{
	mouse_pos.x = x;
	mouse_pos.y = y;
}

PE::Vector PE::InputManager::GetMousePos()
{
	return mouse_pos;
}
