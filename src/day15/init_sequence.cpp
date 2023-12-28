#include <fstream>
#include <iostream>
#include <sstream>

#include "init_sequence.hpp"

cInitSequence::cInitSequence(const std::string& arg_path) :
	objects(),
	objectsHashSum(0U),
	boxes()
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
		objectsHashSum += Hash(object);
	}

	for (auto& object : objects)
	{
		ProcessObject(object);
	}
}

void cInitSequence::ProcessObject(const std::string& arg_object)
{
	sLens lens(arg_object);
	uint8_t boxIndex = Hash(lens.label);

	if (lens.operation == sLens::eOperation::ADD)
	{
		boxes.at(boxIndex).Add(lens);
	}
	else
	{
		boxes.at(boxIndex).Remove(lens);
	}
}


uint8_t cInitSequence::Hash(const std::string& arg_string)
{
	uint16_t result = 0U;

	for (char c : arg_string)
	{
		result = (((result)+(uint16_t)c) * 17U) % 256U;
	}

	return static_cast<uint8_t>(result);
}

uint32_t cInitSequence::ObjectsHashSum(void) const
{
	return objectsHashSum;
}

uint32_t cInitSequence::FocusingPower(void) const
{
	uint32_t sum = 0U;

	for (uint16_t i = 0; i < boxes.size(); i++)
	{
		const cBox& box = boxes[i];
		sum += box.FocusingPower(i + 1U);
	}

	return sum;
}
