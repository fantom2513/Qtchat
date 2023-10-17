#pragma once
#include <string>
#include <fstream>
#include <mutex>

class Logger
{
private:
	std::fstream _fileStream;
    std::mutex _mutex;

public:
	Logger(std::string filename);
	~Logger();

	bool writoToFile(std::string text);
	std::string readFromFileOneLine();
};

