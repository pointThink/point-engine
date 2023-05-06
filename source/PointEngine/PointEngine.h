#pragma once

// this is required otherwise the linker throws an error
// no touchy - PT
#define SDL_MAIN_HANDLED

#include "Game.h"
#include "Logging.h"
#include "Rendering/Window.h"
#include "Rendering/Sprite.h"
#include "Vector.h"
#include "Entity/Entity.h"
#include "Input.h"
#include "Collision.h"
#include "Console/Console.h"
#include "Hardware/HardwareInfo.h"
#include "Error/Error.h"

#if defined(COMP_MSVC)
	#if defined _WIN64
		#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
	#else
		#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
	#endif
#endif