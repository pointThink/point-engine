#pragma once

#include <unordered_map>
#include <string>
#include <chrono>
#include <ctime>

#include "Core.h"
#include "Vector.h"

#define PE_KEY_ESCAPE 41
#define PE_KEY_F1 58
#define PE_KEY_F2 59
#define PE_KEY_F3 60
#define PE_KEY_F4 61
#define PE_KEY_F5 62
#define PE_KEY_F6 63
#define PE_KEY_F7 64
#define PE_KEY_F8 65
#define PE_KEY_F9 66
#define PE_KEY_F10 67
#define PE_KEY_F11 68
#define PE_KEY_F12 69
#define PE_KEY_PRTSC 70
#define PE_KEY_INSERT 73
#define PE_KEY_DELETE 76
#define PE_KEY_BACKSPACE 42
#define PE_KEY_ENTER 40

#define PE_KEY_1 30
#define PE_KEY_2 31
#define PE_KEY_3 32
#define PE_KEY_4 33
#define PE_KEY_5 34
#define PE_KEY_6 35
#define PE_KEY_7 36
#define PE_KEY_8 37
#define PE_KEY_9 38
#define PE_KEY_0 39
#define PE_KEY_MINUS 45
#define PE_KEY_EQUALS 45

#define PE_KEY_NP_1 89
#define PE_KEY_NP_2 90
#define PE_KEY_NP_3 91
#define PE_KEY_NP_4 92
#define PE_KEY_NP_5 93
#define PE_KEY_NP_6 94
#define PE_KEY_NP_7 95
#define PE_KEY_NP_8 96
#define PE_KEY_NP_9 97
#define PE_KEY_NP_0 98
#define PE_KEY_NP_PLUS 87
#define PE_KEY_NP_MINUS 86
#define PE_KEY_NP_TIMES 85
#define PE_KEY_NP_SLASH 84
#define PE_KEY_NP_DOT 99

#define PE_KEY_Q 20
#define PE_KEY_W 26
#define PE_KEY_E 8
#define PE_KEY_R 21
#define PE_KEY_T 23
#define PE_KEY_Y 28
#define PE_KEY_U 24
#define PE_KEY_I 12
#define PE_KEY_O 18
#define PE_KEY_P 19
#define PE_KEY_A 4
#define PE_KEY_S 22
#define PE_KEY_D 7
#define PE_KEY_F 9
#define PE_KEY_G 10
#define PE_KEY_H 11
#define PE_KEY_J 13
#define PE_KEY_K 14
#define PE_KEY_L 15
#define PE_KEY_Z 29
#define PE_KEY_X 27
#define PE_KEY_C 6
#define PE_KEY_V 25
#define PE_KEY_B 5
#define PE_KEY_N 17
#define PE_KEY_M 16

#define PE_KEY_UP 82
#define PE_KEY_DOWN 81
#define PE_KEY_LEFT 80
#define PE_KEY_RIGHT 79

#define PE_KEY_COLON 54
#define PE_KEY_DOT 55
#define PE_KEY_SEMICOLON 51
#define PE_KEY_QUOTE 52
#define PE_KEY_SBRACKET_OPEN 47
#define PE_KEY_SBRACKET_CLOSE 48
#define PE_KEY_BACK_SLASH 49
#define PE_KEY_FORWARD_SLASH 56

#define PE_KEY_ENTER 88
#define PE_KEY_LCTRL 224
#define PE_KEY_LSHIFT 225
#define PE_KEY_RCTRL 228
#define PE_KEY_RSHIFT 229
#define PE_KEY_ALT 226
#define PE_KEY_ALTGR 230
#define PE_KEY_TAB 43

#define PE_MOUSE_LEFT 1
#define PE_MOUSE_MIDDLE 2
#define PE_MOUSE_RIGHT 3
#define PE_MOUSE_4 4
#define PE_MOUSE_5 5
#define PE_MOUSE_6 6
#define PE_MOUSE_7 7
#define PE_MOUSE_8 8
#define PE_MOUSE_9 9
#define PE_MOUSE_10 10

namespace PE
{
	enum InputType
	{
		INPUT_MOUSE,
		INPUT_KEYBOARD
	};

	class ENGINE_API InputState
	{
		bool down = false;
		bool down_on_last_frame = false;
		std::chrono::high_resolution_clock::time_point pressed_at;

		public:
		void UpdateLastFrameState();
		void SetDown(bool state);
		bool IsDown();
		bool WasDown();

		double PressedFor();
	};

	class Binding
	{
		public:
		InputType type;
		int code;
	};

	class ENGINE_API InputManager
	{
		std::unordered_map<std::string, Binding> bindings;
		InputState key_states[255];
		InputState button_states[10];
		PE::Vector mouse_pos;

		public:
		void SetMousePos(int x, int y);
		PE::Vector GetMousePos();

		InputState * GetButtonState(int button);
		InputState * GetKeyState(int key);
		InputState * GetBindState(std::string bind);

		void BindKey(std::string name, int key);
		void BindButton(std::string name, int button);

		void UpdateLastFrameStates();
	};
}
