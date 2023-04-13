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

		int inputCode;
		int exitCode;
		Vector mouseMovement;
	};

	void ENGINE_API CallEventFunction(EventType eventType, EventParameters eventParameters);

	inline void (*eventHandler)(EventType, EventParameters) = nullptr;
};
