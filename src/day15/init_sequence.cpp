#include <fstream>
#include <iostream>
#include <sstream>

#include "init_sequence.hpp"

cInitSequence::cInitSequence(const std::string& arg_path) :
	objects()
{
	std::ifstream file(arg_path);

	if (!file.is_open())
	{
		std::cout << "File is not found." << std::endl;
		exit(EXIT_FAILURE);
	}

	std::stringstream strStream;
	strStream << file.rdbuf();
	file.close();

	while (strStream.good())
	{
		std::string object;
		std::getline(strStream, object, ',');
		objects.push_back(object);
	}
}

uint8_t cInitSequence::Hash(const std::string& arg_string)
{
	uint16_t result = 0U;

	for (char c : arg_string)
	{
		result += (uint16_t)c;
		result *= 17U;
		result %= 256U;
	}

	return static_cast<uint8_t>(result);
}

uint32_t cInitSequence::HashSum(void) const
{
	uint32_t sum = 0U;

	for (auto& object : objects)
	{
		sum += Hash(object);
	}

	return sum;
}
