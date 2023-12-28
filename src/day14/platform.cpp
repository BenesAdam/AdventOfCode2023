#include <iostream>
#include <fstream>

#include "platform.hpp"

cPlatform::cPlatform(const std::string& arg_path) :
	width(0U),
	height(0U),
	data()
{
	std::ifstream file(arg_path);

	if (!file.is_open())
	{
		std::cout << "File is not found." << std::endl;
	}

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

void cPlatform::Print(void) const
{
	for (uint16_t i = 0U; i < height; i++)
	{
		for (uint16_t j = 0U; j < height; j++)
		{
			std::cout << data[i][j];
		}
		std::cout << std::endl;
	}
}

uint32_t cPlatform::TotalNorthLoad(void)
{
	TiltNorth();

	uint32_t totalLoad = 0U;

	for (uint16_t i = 0U; i < height; i++)
	{
		const uint16_t rowWorth = height - i;
		totalLoad += rowWorth * NumberOfRoundedRocks(i);
	}

	return totalLoad;
}

void cPlatform::TiltNorth(void)
{
	for (uint16_t i = 0U; i < height; i++)
	{
		for (uint16_t j = 0U; j < height; j++)
		{
			if (data[i][j] == 'O')
			{
				TiltNorth(i, j);
			}
		}
	}
}

void cPlatform::TiltNorth(const uint16_t arg_i, const uint16_t arg_j)
{
	if (arg_i == 0U)
	{
		return;
	}

	if (data[arg_i - 1U][arg_j] == '.')
	{
		data[arg_i][arg_j] = '.';
		data[arg_i - 1U][arg_j] = 'O';
		TiltNorth(arg_i - 1U, arg_j);
	}
}

uint16_t cPlatform::NumberOfRoundedRocks(const uint16_t arg_i) const
{
	uint16_t rocks = 0U;

	for (auto rock : data[arg_i])
	{
		if (rock == 'O')
		{
			rocks++;
		}
	}

	return rocks;
}
