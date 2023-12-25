#include <fstream>
#include <iostream>
#include <stack>

#include "image.hpp"

cImage::cImage(void) :
	width(0U),
	height(0U),
	data(),
	positions(),
	expansion(0U)
{
}

cImage::cImage(const std::string& arg_path, const uint64_t arg_expansion) :
	cImage()
{
	expansion = (arg_expansion > 0U) ? (arg_expansion - 1U) : 0U;
	ParseFile(arg_path);
	CalculatePositions();
	ExpandPositions();
}

void cImage::ParseFile(const std::string& arg_path)
{
	std::ifstream file(arg_path);

	if (!file.is_open())
	{
		std::cout << "File is not found." << std::endl;
		exit(EXIT_FAILURE);
	}

	data.clear();
	height = 0U;
	width = 0U;

	std::string line;

	while (!file.eof())
	{
		std::getline(file, line);
		height++;
		data.push_back(line);
	}

	width = line.size();

	file.close();
}

void cImage::CalculatePositions(void)
{
	positions.clear();

	for (uint16_t i = 0U; i < height; i++)
	{
		for (uint16_t j = 0U; j < width; j++)
		{
			if (data[i][j] == '#')
			{
				positions.push_back(sPosition<uint64_t>(i, j));
			}
		}
	}
}

void cImage::ExpandPositions(void)
{
	ExpandVertical();
	ExpandHorizontal();
}

void cImage::ExpandVertical(void)
{
	std::stack<uint16_t> rowsToExpand;

	// Find all rows that should be expanded
	for (uint16_t i = 0U; i < height; i++)
	{
		bool expands = true;
		for (uint16_t j = 0U; j < width; j++)
		{
			if (data[i][j] != '.')
			{
				expands = false;
				break;
			}
		}

		if (expands)
		{
			rowsToExpand.push(i);
		}
	}

	// Expand these rows
	std::vector<sPosition<uint64_t>> expandedPositions(positions);

	while (!rowsToExpand.empty())
	{
		uint16_t row = rowsToExpand.top();
		rowsToExpand.pop();

		for (uint16_t i = 0U; i < positions.size(); i++)
		{
			if (positions.at(i).i >= row)
			{
				expandedPositions.at(i).i += expansion;
			}
		}
	}

	positions = expandedPositions;
}

void cImage::ExpandHorizontal(void)
{
	std::stack<uint16_t> columnsToExpand;

	// Find all columns that should be expanded
	for (uint16_t j = 0U; j < width; j++)
	{
		bool expands = true;
		for (uint16_t i = 0U; i < height; i++)
		{
			if (data[i][j] != '.')
			{
				expands = false;
				break;
			}
		}

		if (expands)
		{
			columnsToExpand.push(j);
		}
	}

	// Expand these columns
	std::vector<sPosition<uint64_t>> expandedPositions(positions);

	while (!columnsToExpand.empty())
	{
		uint16_t column = columnsToExpand.top();
		columnsToExpand.pop();

		for (uint16_t i = 0U; i < positions.size(); i++)
		{
			if (positions.at(i).j >= column)
			{
				expandedPositions.at(i).j += expansion;
			}
		}
	}

	positions = expandedPositions;
}

uint64_t cImage::SumOfDistances(void)
{
	uint64_t sum = 0U;

	for (uint16_t i = 0U; i < positions.size(); i++)
	{
		for (uint16_t j = (i + 1U); j < positions.size(); j++)
		{
			sPosition<uint64_t>& position1 = positions.at(i);
			sPosition<uint64_t>& position2 = positions.at(j);
			uint64_t distance = position1.ManhattanDistance(position2);
			sum += distance;
		}
	}

	return sum;
}
