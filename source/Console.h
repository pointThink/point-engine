#pragma once

#include <string>

#include "ConVars.h"

namespace PE
{
	class ENGINE_API Console
	{
		public:
		Console();
		~Console();

		std::string contents = "";
		char command[255] = "";
		bool is_open = false;

		ConVarManager * convar_manager;

		void RunCommand(std::string cmd);
		void Draw();
		void Clear();
	};
}
