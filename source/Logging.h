#pragma once

#include <string>

class Logger
{
	public:
	Logger(std::string log_file);
	
	std::string log_file;
	bool print_to_stdout;

	void LogError(std::string string);
	void LogWarning(std::string string);
	void LogInfo(std::string string);
	void LogGeneric(std::string string);
};