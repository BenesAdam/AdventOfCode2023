#include <fstream>
#include <iostream>
#include <stack>

#include "image.hpp"

cImage::cImage(void) :
	width(0U),
	height(0U),
	data(),
	positions()
{
}

cImage::cImage(const cImage* const arg_image)
{
	width = arg_image->width;
	height = arg_image->height;

	for (auto& row : arg_image->data)
	{
		data.push_back(row);
	}

	for (auto& position : positions)
	{
		positions.push_back(position);
	}
}

cImage::cImage(const std::string& arg_path) :
	cImage()
{
	ParseFile(arg_path);
	RecalculatePositions();
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

void cImage::RecalculatePositions(void)
{
	positions.clear();

	for (uint16_t i = 0U; i < height; i++)
	{
		for (uint16_t j = 0U; j < width; j++)
		{
			if (data[i][j] == '#')
			{
				positions.push_back(sPosition<uint16_t>(i, j));
			}
		}
	}
}

cImage cImage::GetExpanded(const cImage& arg_image)
{
	cImage expanded(&arg_image);
	expanded.Expand();
	expanded.RecalculatePositions();
	return expanded;
}

void cImage::Expand(void)
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
	while (!rowsToExpand.empty())
	{
		uint16_t row = rowsToExpand.top();
		rowsToExpand.pop();

		data.insert(data.begin() + row, std::string(width, '.'));
		height++;
	}
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
	while (!columnsToExpand.empty())
	{
		uint16_t column = columnsToExpand.top();
		columnsToExpand.pop();

		for (auto& row : data)
		{
			row.insert(row.begin() + column, '.');
		}
		width++;
	}
}

uint32_t cImage::SumOfDistances(void)
{
	uint32_t sum = 0U;

	for (uint16_t i = 0U; i < positions.size(); i++)
	{
		for (uint16_t j = (i + 1U); j < positions.size(); j++)
		{
			sPosition<uint16_t>& position1 = positions.at(i);
			sPosition<uint16_t>& position2 = positions.at(j);
			uint32_t distance = static_cast<uint32_t>(ManhattanDistance<uint16_t, int32_t>(position1, position2));
			sum += distance;
		}
	}

	return sum;
}

uint32_t cImage::SumOfExpandedDistances(void)
{
	cImage expanded = cImage::GetExpanded(*this);
	return expanded.SumOfDistances();
}

void cImage::Print(void) const
{
	for (uint16_t i = 0U; i < height; i++)
	{
		std::cout << data[i] << std::endl;
	}
}

void cImage::PrintPositions(void) const
{
	for (auto& position : positions)
	{
		std::cout << position << " ";
	}
	std::cout << std::endl;
}
