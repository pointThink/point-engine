#include "Event.h"

namespace PE
{
	void CallEventFunction(EventType eventType, EventParameters eventParameters)
	{
		if (eventHandler != nullptr)
		{
			eventHandler(eventType, eventParameters);
		}
	}
};

PE::EventParameters::EventParameters(int ic, int ec, Vector mm)
{
	inputCode = ic;
	exitCode = ec;
	mouseMovement = mm;
}
