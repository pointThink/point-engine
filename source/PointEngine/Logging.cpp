#define _CRT_SECURE_NO_WARNINGS // god damnit msvc

#include "Logging.h"

#include <iostream>
#include <ctime>
#include <cstring>

void PE::LogInit(PE::Console * a_console)
{
	log_file.open("log.txt");

	console = a_console;
}

void PE::LogDeInit()
{
	//log_file.close();
}

void PE::LogError(std::string string)
{
	LogGeneric("[ERROR] " + string);
}

void PE::LogWarning(std::string string)
{
	LogGeneric("[WARNING] " + string);
}

void PE::LogInfo(std::string string)
{
	LogGeneric("[INFO] " + string);
}

void PE::LogGeneric(std::string string)
{
	std::string output_string;

	time_t t;
	time(&t);

	// i hate strings in c++, i mean just look at this shit - PT
	output_string = std::string("[") + std::string(strtok(ctime(&t), "\n")) + std::string("] ") + string + std::string("\n");

	console->Print(output_string);

	// write the line to the file
	log_file << output_string;
}
