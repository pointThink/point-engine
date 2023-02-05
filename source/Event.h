#pragma once

#include "Core.h"
#include "Vector.h"

namespace PE
{
	enum EventType
	{
		GAME_UPDATE, GAME_DRAW, GAME_TICK, GAME_CLOSED, GAME_INIT,
		MOUSE_MOVED, MOUSE_BUTTON_PRESSED, KEY_PRESSED
	};

	class ENGINE_API EventParameters
	{
		public:
		EventParameters(int ic, int ec, Vector mm);

		int input_code;
		int exit_code;
		Vector mouse_movement;
	};

	void ENGINE_API CallEventFunction(EventType event_type, EventParameters event_parameters);

	inline void (*event_handler)(EventType, EventParameters) = nullptr;
};
