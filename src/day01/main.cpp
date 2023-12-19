#include <iostream>
#include <fstream>
#include <sstream>

#include "main.hpp"


int main(int argc, char* argv[])
{
	std::string input = SOURCE_DIR"/day01/input";
	//std::string input = SOURCE_DIR"/day01/test1";

	std::ifstream file;
	file.open(input);

	if (file.is_open())
	{
		uint32_t sum = 0U;
		std::string line;
		while (!file.eof())
		{
			file >> line;
			sum += GetCalibrationValue(line);
		}

		std::cout << "Sum of all calibration values is: " << sum << std::endl;
	}
	else
	{
		std::cout << "File did not found." << std::endl;
	}

	file.close();

	return 0;
}

uint32_t GetCalibrationValue(const std::string& arg_line)
{
	char firstDigit = '0';
	char lastDigit = '0';

	for (auto it = arg_line.begin(); it != arg_line.end(); it++)
	{
		const char c = *it;
		if (isdigit(c))
		{
			firstDigit = c;
			break;
		}
	}

	for (auto it = arg_line.rbegin(); it != arg_line.rend(); it++)
	{
		const char c = *it;
		if (isdigit(c))
		{
			lastDigit = c;
			break;
		}
	}

	std::string number = {firstDigit, lastDigit};

	return atoi(number.c_str());
}
