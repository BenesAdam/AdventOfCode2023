#include <iostream>
#include <fstream>

#include "map.hpp"

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
			start = { height - 1U, static_cast<uint32_t>(startJ) };
		}
	}

	width = line.size();

	file.close();
}

uint32_t cMap::GardensWithinReach(const uint32_t arg_steps)
{
	std::set<sPosition<uint32_t>> positions;
	positions.insert(start);

	for (uint32_t i = 0U; i < arg_steps; i++)
	{
		std::set<sPosition<uint32_t>> nextPositions;
		for (auto& position : positions)
		{
			StepFromLocation(position, nextPositions);
		}

		positions = nextPositions;
	}

	return positions.size();
}

void cMap::Print(std::set<sPosition<uint32_t>>& arg_positions) const
{
	for (uint32_t i = 0U; i < height; i++)
	{
		for (uint32_t j = 0U; j < width; j++)
		{
			const bool positionVisited = (arg_positions.find(sPosition<uint32_t>(i, j)) != arg_positions.end());
			const char c = positionVisited ? cMap::Visited : data[i][j];
			std::cout << c;
		}

		std::cout << std::endl;
	}
}

void cMap::StepFromLocation(const sPosition<uint32_t>& arg_position, std::set<sPosition<uint32_t>>& arg_positions)
{
	static const std::vector<std::pair<int32_t, int32_t>> offsets =
	{
		{-1,  0},
		{ 0,  1},
		{ 1,  0},
		{ 0, -1},
	};

	for (auto& offset : offsets)
	{
		const sPosition<uint32_t> neighbour(arg_position.i - offset.first, arg_position.j - offset.second);
		if (!neighbour.IsInBoundary(width, height))
		{
			continue;
		}

		const char c = data[neighbour.i][neighbour.j];
		if (c == cMap::Rock)
		{
			continue;
		}

		arg_positions.insert(neighbour);
	}
}
