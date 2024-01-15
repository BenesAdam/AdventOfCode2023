#include <iostream>
#include <fstream>

#include "map.hpp"
#include "numeric.hpp"

cMap::cMap(const std::string& arg_path) :
	width(0U),
	height(0U),
	data(),
	start()
{
	std::ifstream file(arg_path);

	if (!file.is_open())
	{
		std::cout << "File is not found." << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string line;
	while (!file.eof())
	{
		std::getline(file, line);
		height++;
		data.push_back(line);

		const size_t startJ = line.find(cMap::Start);
		if (startJ != std::string::npos)
		{
			start = { static_cast<int64_t>(height - 1U), static_cast<int64_t>(startJ) };
		}
	}

	width = line.size();

	file.close();
}

void cMap::Compute(const uint32_t arg_steps)
{
	std::vector<uint32_t> yValues;
	uint32_t result;

	std::set<sPosition<int64_t>> positions;
	positions.insert(start);

	const uint32_t max = 65U + 131U * 2U + 1U;
	for (uint32_t i = 0U; i < max; i++)
	{
		if ((i % 131U) == 65U)
		{
			yValues.push_back(positions.size());
		}
		if (i == arg_steps)
		{
			result = positions.size();
		}

		std::set<sPosition<int64_t>> nextPositions;
		for (auto& position : positions)
		{
			StepFromLocation(position, nextPositions);
		}

		positions = nextPositions;
	}

	// Result part 1
	std::cout << "Part 1: " << std::to_string(result) << std::endl;

	// Part 2
	std::cout << "Part 2:" << std::endl;
	std::cout << "1. Go to: https://www.wolframalpha.com/input?i=quadratic+fit+calculator&assumption=%7B%22F%22%2C+%22QuadraticFitCalculator%22%2C+%22data3x%22%7D+-%3E%22%7B0%2C+1%2C+2%7D%22&assumption=%7B%22F%22%2C+%22QuadraticFitCalculator%22%2C+%22data3y%22%7D+-%3E%22%7B1%2C+1%2C+1%7D%22" << std::endl;
	std::cout << "2. Paste Y values to text box: {";

	for (uint8_t i = 0U; i < yValues.size(); i++)
	{
		std::cout << yValues[i] << ((i != yValues.size() - 1U) ? ", " : "");
	}
	std::cout << "}" << std::endl;

	std::cout << "3. Click on \"Compute\"" << std::endl;
	std::cout << "4. Click on equation below \"Least-squares best fit\"" << std::endl;
	std::cout << "5. Paste this at the end of equation: ,x=" << std::to_string((26501365 - 65) / 131) << std::endl;
	std::cout << "6. Hit \"Enter\" and see what is in result." << std::endl;
}

void cMap::StepFromLocation(const sPosition<int64_t>& arg_position, std::set<sPosition<int64_t>>& arg_positions)
{
	static const std::vector<std::pair<int64_t, int64_t>> offsets =
	{
		{-1,  0},
		{ 0,  1},
		{ 1,  0},
		{ 0, -1},
	};

	for (auto& offset : offsets)
	{
		const sPosition<int64_t> neighbour(arg_position.i + offset.first, arg_position.j + offset.second);
		const char c = data[nsNumeric::Modulo(neighbour.i, height)][nsNumeric::Modulo(neighbour.j, width)];
		if (c == cMap::Rock)
		{
			continue;
		}

		arg_positions.insert(neighbour);
	}
}
