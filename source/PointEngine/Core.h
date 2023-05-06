#pragma once

//#include "backward.hpp"

#if defined(WINDOWS64)
	#if defined(ENGINE_BUILD)
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif
#else
	#error Only 64bit windows is supported for now
#endif

#if defined(COMP_MSVC)
	#define COMPILER "MSVC"


#elif defined (COMP_GCC)
	#define COMPILER "GCC"
#else
	#define COMPILER "UNKNOWN"
#endif

#define PE_VERSION "alpha 0.7"
