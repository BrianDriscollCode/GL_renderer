#ifndef DEBUGOUTPUT_H
#define DEBUGOUTPUT_H

#include <string>
#include <iostream>

class DebugOutput
{
public:
	std::string green;
	std::string red;
	std::string yellow;
	std::string endColor;

	DebugOutput(bool activate)
	{
		green = "\033[1;32m";
		red = "\033[1;31m";
		yellow = "\033[1;33m";
		endColor = "\033[0m";
	}


	void outputGreenText(const char* text, const char* text2 = "", const char* text3 = "") const
	{
		std::cout << green << text << text2 << text3 << endColor << std::endl;
	}

	void outputRedText(const char* text, const char* text2 = "", const char* text3 = "") const
	{
		std::cout << red << text << text2 << text3 << endColor <<std::endl;
	}

	void outputYellowText(const char* text, const char* text2 = "", const char* text3 = "") const
	{
		std::cout << yellow << text << text2 << text3 << endColor << std::endl;
	}



};


#endif