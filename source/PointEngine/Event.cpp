#include "Event.h"

namespace PE
{
	void CallEventFunction(EventType event_type, EventParameters event_parameters)
	{
		if (event_handler != nullptr)
		{
			event_handler(event_type, event_parameters);
		}
	}
};

PE::EventParameters::EventParameters(int ic, int ec, Vector mm)
{
	input_code = ic;
	exit_code = ec;
	mouse_movement = mm;
}
