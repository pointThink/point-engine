#include "Input.h"

#include "Logging.h"

namespace PE
{
	void InputState::SetDown(bool down)
	{
		this->down = down;

		pressed_at = std::chrono::high_resolution_clock::now();
	}

	void InputState::UpdateLastFrameState()
	{
		down_on_last_frame = down;
	}

	bool InputState::IsDown()
	{
		return down;
	}

	bool InputState::WasDown()
	{
		return down_on_last_frame;
	}

	double InputState::PressedFor()
	{
		auto pressed_for = std::chrono::high_resolution_clock::now() - pressed_at;
		return pressed_for.count() * 100000;
	}

	void InputManager::BindKey(std::string name, int key)
	{
		bindings[name] = { INPUT_KEYBOARD, key };
	}

	void InputManager::BindButton(std::string name, int button)
	{
		bindings[name] = { INPUT_MOUSE, button };
	}

	void InputManager::SetMousePos(int x, int y)
	{
		mouse_pos.x = x;
		mouse_pos.y = y;
	}

	Vector InputManager::GetMousePos()
	{
		return mouse_pos;
	}

	InputState* InputManager::GetKeyState(int key)
	{
		return &key_states[key];
	}

	InputState* InputManager::GetButtonState(int button)
	{
		return &button_states[button];
	}

	InputState* InputManager::GetBindState(std::string name)
	{
		InputState* state = nullptr;
		Binding bind = bindings[name];

		if (bind.type == INPUT_KEYBOARD)
			state = GetKeyState(bind.code);
		else if (bind.type == INPUT_MOUSE)
			state = GetButtonState(bind.code);

		return state;
	}

	void InputManager::UpdateLastFrameStates()
	{
		for (InputState& state : key_states)
		{
			state.UpdateLastFrameState();
		}

		for (InputState& state : button_states)
		{
			state.UpdateLastFrameState();
		}
	}

}