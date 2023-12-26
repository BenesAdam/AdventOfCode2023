#include <iostream>

#include "pattern.hpp"

std::list<cPattern> cPattern::ParseFile(const std::string& arg_path)
{
	std::ifstream file(arg_path);

	if (!file.is_open())
	{
		std::cout << "File is not found." << std::endl;
		exit(EXIT_FAILURE);
	}

	std::list<cPattern> patterns;

	while (!file.eof())
	{
		cPattern pattern(file);
		patterns.push_back(pattern);
	}

	file.close();

	return patterns;
}

cPattern::cPattern(void) :
	width(0U),
	height(0U),
	data()
{
}

cPattern::cPattern(std::ifstream& arg_file) :
	cPattern()
{
	std::string line;

	while (!arg_file.eof())
	{
		std::getline(arg_file, line);

		if (line == "")
		{
			break;
		}

		if (data == "")
		{
			width = line.size();
		}

		height++;
		data += line;
	}
}

void cPattern::Print(void) const
{
	for (uint16_t i = 0U; i < height; i++)
	{
		for (uint16_t j = 0U; j < width; j++)
		{
			std::cout << Get(i, j);
		}
		std::cout << std::endl;
	}
}

uint32_t cPattern::ReflectionSummarization(std::list<cPattern>& arg_patterns)
{
	uint32_t sum = 0U;

	for (auto& pattern : arg_patterns)
	{
		sum += pattern.ReflectionSummarization();
	}

	return sum;
}

uint32_t cPattern::ReflectionSummarization(void) const
{
	uint32_t sum = 0U;

	// Vertical
	uint16_t verticalIndex = FindVerticalReflection();
	if (verticalIndex != UINT16_MAX)
	{
		sum += verticalIndex + 1U;
	}

	// Horizontal
	uint16_t horizontalIndex = FindHorizontalReflection();
	if (horizontalIndex != UINT16_MAX)
	{
		sum += (horizontalIndex + 1U) * 100U;
	}

	return sum;
}

uint16_t cPattern::FindVerticalReflection(void) const
{
	cPattern rotated = GetRotated();
	return rotated.FindHorizontalReflection();
}

cPattern cPattern::GetRotated(void) const
{
	cPattern rotated;

	for (uint16_t j = 0U; j < width; j++)
	{
		for (uint16_t i = 0U; i < height; i++)
		{
			rotated.data += Get(i, j);
		}
	}

	rotated.width = height;
	rotated.height = width;

	return rotated;
}

uint16_t cPattern::FindHorizontalReflection(void) const
{
	std::vector<std::string> rows;
	for (uint16_t i = 0U; i < height; i++)
	{
		std::string row = data.substr(i * width, width);
		rows.push_back(row);
	}

	for (uint16_t firstRowIndex = 0U; firstRowIndex < (height - 1U); firstRowIndex++)
	{
		uint16_t secondRowIndex = firstRowIndex + 1U;
		if (CheckHorizontalReflection(rows, firstRowIndex, secondRowIndex))
		{
			return firstRowIndex;
		}
	}

	return UINT16_MAX;
}

bool cPattern::CheckHorizontalReflection(std::vector<std::string>& arg_rows, const uint16_t arg_firstRowIndex, const uint16_t arg_secondRowIndex) const
{
	// Check current
	if (arg_rows[arg_firstRowIndex] != arg_rows[arg_secondRowIndex])
	{
		return false;
	}

	// Expansion is not possible
	if ((arg_firstRowIndex == 0U) || (arg_secondRowIndex == (height - 1U)))
	{
		return true;
	}

	// Expand left and right
	return CheckHorizontalReflection(arg_rows, arg_firstRowIndex - 1U, arg_secondRowIndex + 1U);
}

sPosition<uint16_t> cPattern::GetPosition(const uint32_t arg_index) const
{
	sPosition<uint16_t> position;

	position.i = arg_index / width;
	position.j = arg_index % width;

	return position;
}

uint32_t cPattern::GetIndex(const sPosition<uint16_t>& arg_position) const
{
	return GetIndex(arg_position.i, arg_position.j);
}

uint32_t cPattern::GetIndex(const uint32_t arg_i, const uint32_t arg_j) const
{
	return (arg_i * width) + arg_j;
}

char cPattern::Get(const uint32_t arg_index) const
{
	return data[arg_index];
}

char cPattern::Get(const sPosition<uint16_t>& arg_position) const
{
	return Get(arg_position.i, arg_position.j);
}

char cPattern::Get(const uint32_t arg_i, const uint32_t arg_j) const
{
	return Get(GetIndex(arg_i, arg_j));
}

bool cPattern::IsInBoundaries(const uint32_t arg_index) const
{
	return arg_index < data.size();
}

bool cPattern::IsInBoundaries(const sPosition<uint16_t>& arg_position) const
{
	return IsInBoundaries(arg_position.i, arg_position.j);
}

bool cPattern::IsInBoundaries(const uint32_t arg_i, const uint32_t arg_j) const
{
	return (arg_i < height) && (arg_j < width);
}
