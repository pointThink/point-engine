#pragma once

#include <string>

namespace PE
{
	class Console
	{
		public:
		std::string contents = "";
		char command[255] = "";
		bool is_open;

		void RunCommand(std::string cmd);
		void Draw();
		void Clear();
	};
}
