#include "Error/Error.h"

#include <Windows.h>

namespace PE
{
	namespace Error
	{
		void CriticalError(std::string message)
		{
			MessageBox(MB_OK, message.c_str(), "PointEngine Error", MB_ICONSTOP);
		}
	}
}