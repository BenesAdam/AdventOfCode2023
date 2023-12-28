#include <iostream>
#include <fstream>
#include <unordered_map>

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
		data += line;
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
			std::cout << data[GetIndex(i, j)];
		}
		std::cout << std::endl;
	}
}

uint32_t cPlatform::TotalNorthLoadPart1(void)
{
	Tilt(eTiltDirection::NORTH);;
	return TotalNorthLoad();
}

uint32_t cPlatform::TotalNorthLoadPart2(const uint64_t arg_cyclesCount)
{
	std::unordered_map<std::string, uint64_t> cache;
	std::vector<std::string> loopCache;

	std::vector<uint32_t> loads;

	uint64_t indexStart = 0U;
	uint64_t indexEnd = 0U;

	for (uint64_t i = 0U; i < arg_cyclesCount; i++)
	{
		OneCycle();

		if (cache.find(data) != cache.end())
		{
			indexStart = cache[data];
			indexEnd = i;
			break;
		}
		else
		{
			cache[data] = i;
			loopCache.push_back(data);
		}
	}

	uint64_t unprocessed = arg_cyclesCount - (indexEnd + 1U);
	uint64_t loopSize = indexEnd - indexStart;
	std::vector<uint32_t> loop;

	for (uint16_t i = indexStart; i < indexEnd; i++)
	{
		data = *(loopCache.begin() + i);
		uint32_t load = TotalNorthLoad();

		loop.push_back(load);
	}

	uint64_t finalIndex = unprocessed % loopSize;
	uint64_t finalLoad = loop[finalIndex];

	return finalLoad;
}

void cPlatform::OneCycle(void)
{
	Tilt(eTiltDirection::NORTH);
	Tilt(eTiltDirection::WEST);
	Tilt(eTiltDirection::SOUTH);
	Tilt(eTiltDirection::EAST);
}

uint32_t cPlatform::TotalNorthLoad(void)
{
	uint32_t totalLoad = 0U;

	for (uint16_t i = 0U; i < height; i++)
	{
		const uint16_t rowWorth = height - i;
		totalLoad += rowWorth * NumberOfRoundedRocks(i);
	}

	return totalLoad;
}

void cPlatform::Tilt(const cPlatform::eTiltDirection arg_dir)
{
	switch (arg_dir)
	{
	case eTiltDirection::NORTH:
	{
		for (uint16_t i = 0U; i < height; i++)
		{
			for (uint16_t j = 0U; j < width; j++)
			{
				Tilt(arg_dir, i, j);
			}
		}
	}
	break;

	case eTiltDirection::WEST:
	{
		for (uint16_t j = 0U; j < width; j++)
		{
			for (uint16_t i = 0U; i < height; i++)
			{
				Tilt(arg_dir, i, j);
			}
		}
	}
	break;

	case eTiltDirection::SOUTH:
	{
		for (int32_t i = height - 1U; i >= 0; i--)
		{
			for (uint16_t j = 0U; j < width; j++)
			{
				Tilt(arg_dir, i, j);
			}
		}
	}
	break;

	case eTiltDirection::EAST:
	{
		for (int32_t j = width - 1U; j >= 0; j--)
		{
			for (uint16_t i = 0U; i < height; i++)
			{
				Tilt(arg_dir, i, j);
			}
		}
	}
	break;

	default:
		break;
	}
}

void cPlatform::Tilt(const cPlatform::eTiltDirection arg_dir, const uint16_t arg_i, const uint16_t arg_j)
{
	if (IsOnEdge(arg_dir, arg_i, arg_j))
	{
		return;
	}

	uint32_t currentIndex = GetIndex(arg_i, arg_j);
	if (data[currentIndex] != 'O')
	{
		return;
	}

	uint32_t nextIndex = GetNextIndex(arg_dir, arg_i, arg_j);
	if (data[nextIndex] == '.')
	{
		data[currentIndex] = '.';
		data[nextIndex] = 'O';

		sPosition<uint16_t> nextPosition = GetPosition(nextIndex);
		Tilt(arg_dir, nextPosition.i, nextPosition.j);
	}
}

bool cPlatform::IsOnEdge(const cPlatform::eTiltDirection arg_dir, const uint16_t arg_i, const uint16_t arg_j) const
{
	switch (arg_dir)
	{
	case eTiltDirection::NORTH:
		return arg_i == 0U;

	case eTiltDirection::WEST:
		return arg_j == 0U;

	case eTiltDirection::SOUTH:
		return arg_i == (height - 1U);

	case eTiltDirection::EAST:
		return arg_j == (width - 1U);

	default:
		return true;
	}
}

uint32_t cPlatform::GetNextIndex(const cPlatform::eTiltDirection arg_dir, const uint16_t arg_i, const uint16_t arg_j) const
{
	uint16_t nextI = arg_i;
	uint16_t nextJ = arg_j;

	switch (arg_dir)
	{
	case eTiltDirection::NORTH:
		nextI--;
		break;

	case eTiltDirection::WEST:
		nextJ--;
		break;

	case eTiltDirection::SOUTH:
		nextI++;
		break;

	case eTiltDirection::EAST:
		nextJ++;
		break;
	}

	return GetIndex(nextI, nextJ);
}

uint32_t cPlatform::GetIndex(const uint16_t arg_i, const uint16_t arg_j) const
{
	return arg_i * width + arg_j;
}

sPosition<uint16_t> cPlatform::GetPosition(const uint32_t arg_index) const
{
	return sPosition<uint16_t>(arg_index / width, arg_index % width);
}

uint16_t cPlatform::NumberOfRoundedRocks(const uint16_t arg_i) const
{
	uint16_t rocks = 0U;

	uint32_t firstIndex = GetIndex(arg_i, 0);
	for (uint32_t i = firstIndex; i < (firstIndex + width); i++)
	{
		const char rock = data[i];
		if (rock == 'O')
		{
			rocks++;
		}
	}

	return rocks;
}
