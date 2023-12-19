#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

#include "main.hpp"

int main(int argc, char* argv[])
{
	std::string input = SOURCE_DIR"/day01/input";
	//std::string input = SOURCE_DIR"/day01/test1";
	//std::string input = SOURCE_DIR"/day01/test2";

	std::ifstream file;
	file.open(input);

	if (!file.is_open())
	{
		std::cout << "File did not found." << std::endl;
		exit(EXIT_FAILURE);
	}

	uint32_t sum = 0U;
	std::string line;
	while (!file.eof())
	{
		file >> line;
		ConvertSpelledDigits(line);
		sum += GetCalibrationValue(line);
	}

	std::cout << "Sum of all calibration values is: " << sum << std::endl;

	file.close();

	return 0;
}

void ConvertSpelledDigits(std::string& arg_line)
{
	const uint8_t size = 9U;
	const std::string spellings[size] = { "one","two","three","four","five","six","seven","eight","nine" };

	for (uint8_t i = 0U; i < size; i++)
	{
		std::regex re(spellings[i]);
		std::string replecement = "$&" + std::to_string(i + 1U) + "$&"; // Dirty
		arg_line = std::regex_replace(arg_line, re, replecement);
	}
}

uint32_t GetCalibrationValue(const std::string& arg_line)
{
	char firstDigit = '0';
	char lastDigit = '0';

	// Find first digit
	for (auto it = arg_line.begin(); it != arg_line.end(); it++)
	{
		const char c = *it;
		if (isdigit(c))
		{
			firstDigit = c;
			break;
		}
	}

	// Find last digit
	for (auto it = arg_line.rbegin(); it != arg_line.rend(); it++)
	{
		const char c = *it;
		if (isdigit(c))
		{
			lastDigit = c;
			break;
		}
	}

	// Combine them and return
	std::string number = { firstDigit, lastDigit };
	return atoi(number.c_str());
}
