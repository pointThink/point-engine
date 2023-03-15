#include "Input.h"

#include "Logging.h"

void PE::InputState::SetDown(bool down)
{
	this->down = down;

	pressed_at = std::chrono::high_resolution_clock::now();
}

void PE::InputState::UpdateLastFrameState()
{
	down_on_last_frame = down;
}

bool PE::InputState::IsDown()
{
	return down;
}

bool PE::InputState::WasDown()
{
	return down_on_last_frame;
}

double PE::InputState::PressedFor()
{
	auto pressed_for = std::chrono::high_resolution_clock::now() - pressed_at;
	return pressed_for.count() * 100000;
}

void PE::InputManager::BindKey(std::string name, int key)
{
	bindings[name] = {INPUT_KEYBOARD, key};
}

void PE::InputManager::BindButton(std::string name, int button)
{
	bindings[name] = {PE::INPUT_MOUSE, button};
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

PE::InputState * PE::InputManager::GetKeyState(int key)
{
	return &key_states[key];
}

PE::InputState * PE::InputManager::GetButtonState(int button)
{
	return &button_states[button];
}

PE::InputState * PE::InputManager::GetBindState(std::string name)
{
	InputState * state = nullptr;
	Binding bind = bindings[name];

	if (bind.type == INPUT_KEYBOARD)
		state = GetKeyState(bind.code);
	else if (bind.type == INPUT_MOUSE)
		state = GetButtonState(bind.code);

	return state;
}

void PE::InputManager::UpdateLastFrameStates()
{
	for (InputState &state : key_states)
	{
		state.UpdateLastFrameState();
	}

	for (InputState &state : button_states)
	{
		state.UpdateLastFrameState();
	}
}
