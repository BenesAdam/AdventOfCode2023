#include <iostream>
#include <fstream>
#include <regex>

#include "instruction.hpp"

cInstraction::cInstraction(const std::string& arg_str, const bool arg_swapped) :
	direction(UP),
	steps(0U)
{
	std::regex regex("(\\w) (\\d+) \\(#(\\w+)\\)");
	std::smatch m;

	std::regex_match(arg_str, m, regex);

	if (!arg_swapped)
	{
		ParseNotSwapped(m[1].str()[0], m[2]);
	}
	else
	{
		ParseSwapped(m[3]);
	}
}

void cInstraction::ParseNotSwapped(const char arg_direction, const std::string& arg_steps)
{
	switch (arg_direction)
	{
	case 'U':
		direction = UP;
		break;
	case 'R':
		direction = RIGHT;
		break;
	case 'D':
		direction = DOWN;
		break;
	case 'L':
	default:
		direction = LEFT;
		break;
	}

	steps = std::stoi(arg_steps);
}

void cInstraction::ParseSwapped(const std::string& arg_color)
{
	const std::string stepsStr = arg_color.substr(0U, 5U);
	steps = std::stoi(stepsStr, nullptr, 16);

	const std::string directionStr = arg_color.substr(5U);
	direction = static_cast<eDirection>(std::stoi(directionStr));
}

void cInstraction::ParseFile(const std::string& arg_path, std::list<cInstraction>& arg_notSwapped, std::list<cInstraction>& arg_swapped)
{
	std::ifstream file(arg_path);

	if (!file.is_open())
	{
		std::cout << "File is not found." << std::endl;
		exit(EXIT_FAILURE);
	}

	std::list<cInstraction> instructions;
	std::string line;
	while (!file.eof())
	{
		std::getline(file, line);
		arg_notSwapped.push_back(cInstraction(line, false));
		arg_swapped.push_back(cInstraction(line, true));
	}

	file.close();
}

uint64_t cInstraction::ComputeCubicMetersOfLava(const std::list<cInstraction>& arg_instructions)
{	
	uint64_t innerArea = ShoelaceFormula(arg_instructions);
	uint64_t outherBoundaryLength = OuterBoundary(arg_instructions);

	return innerArea + ((outherBoundaryLength / 2ULL) + 1ULL);
}

uint64_t cInstraction::ShoelaceFormula(const std::list<cInstraction>& arg_instructions)
{
	int64_t sum = 0U;

	sPosition<int64_t> currentPosition(0LL);
	sPosition<int64_t> nextPosition;

	for (auto it = arg_instructions.begin(); it != arg_instructions.end(); it++)
	{
		const cInstraction& instruction = *it;

		// get next position
		instruction.GetNextPosition(currentPosition, nextPosition);

		// calculate
		sum += CalculateIncrement(currentPosition, nextPosition);

		// set current position for next instruction
		currentPosition = nextPosition;
	}

	return abs(sum) / 2LL;
}

void cInstraction::GetNextPosition(const sPosition<int64_t>& arg_current, sPosition<int64_t>& arg_next) const
{
	arg_next = arg_current;

	sPosition<int64_t> offset(0LL);
	switch (direction)
	{
	case cInstraction::UP:
		offset.i -= steps;
		break;
	case cInstraction::RIGHT:
		offset.j += steps;
		break;
	case cInstraction::DOWN:
		offset.i += steps;
		break;
	case cInstraction::LEFT:
		offset.j -= steps;
		break;
	default:
		break;
	}

	arg_next += offset;
}

int64_t cInstraction::CalculateIncrement(const sPosition<int64_t>& arg_currentPosition, const sPosition<int64_t>& arg_nextPosition)
{
	const int64_t left = (-arg_currentPosition.i) + (-arg_nextPosition.i);
	const int64_t right = arg_currentPosition.j - arg_nextPosition.j;
	return left * right;
}

uint64_t cInstraction::OuterBoundary(const std::list<cInstraction>& arg_instructions)
{
	uint64_t length = 0U;

	for (auto& instruction : arg_instructions)
	{
		length += instruction.steps;
	}

	return length;
}
