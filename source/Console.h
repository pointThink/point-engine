#pragma once

#include <string>

#include "ConVars.h"

namespace PE
{
	class Console
	{
		public:
		Console();
		~Console();

		std::string contents = "";
		char command[255] = "";
		bool is_open;

		ConVarManager * convar_manager;

		void RunCommand(std::string cmd);
		void Draw();
		void Clear();
	};
}
