#include "Logging.h"

#include <iostream>
#include <ctime>
#include <cstring>

Logger::Logger(std::string log_file)
{
	this->log_file = log_file;

	print_to_stdout = true;
}

void Logger::LogError(std::string string)
{
	LogGeneric("[ERROR] " + string);
}

void Logger::LogWarning(std::string string)
{
	LogGeneric("[WARNING] " + string);
}

void Logger::LogInfo(std::string string)
{
	LogGeneric("[INFO] " + string);
}

void Logger::LogGeneric(std::string string)
{
	std::string output_string;

	time_t t;
	time(&t);

	// i hate strings in c++
	output_string = std::string("[") + std::string(strtok(ctime(&t), "\n")) + std::string("]") + string + std::string("\n");

	// for now no file output
	// ill implement it later
	if (print_to_stdout)
		std::cout << output_string;
}