#pragma once

#if defined(WINDOWS64)
	#if defined(ENGINE_BUILD)
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif
#else
	#error Only 64bit windows is supported for now
#endif

#define PE_VERSION "alpha 0.3"
