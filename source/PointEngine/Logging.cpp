#define _CRT_SECURE_NO_WARNINGS // god damnit msvc

#include "Logging.h"

#include <iostream>
#include <ctime>
#include <cstring>

namespace PE
{
	void LogInit(Console* a_console)
	{
		log_file.open("log.txt");

		console = a_console;
	}

	void LogDeInit()
	{
		log_file.close();
	}

	void LogError(std::string string)
	{
		LogGeneric("[ERROR] " + string);
	}

	void LogWarning(std::string string)
	{
		LogGeneric("[WARNING] " + string);
	}

	void LogInfo(std::string string)
	{
		LogGeneric("[INFO] " + string);
	}

	void LogGeneric(std::string string)
	{
		std::string output_string;

		time_t t;
		time(&t);

		// i hate strings in c++, i mean just look at this shit - PT
		output_string = std::string("[") + std::string(strtok(ctime(&t), "\n")) + std::string("] ") + string + std::string("\n");

		std::cout << output_string << std::endl;
		console->Print(output_string);

		// write the line to the file
		log_file << output_string;
	}
}

