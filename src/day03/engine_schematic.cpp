#include <fstream>
#include <iostream>

#include "engine_schematic.hpp"

cEngineSchematic::cEngineSchematic(const std::string& arg_path) :
	size(0U),
	data()
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
		file >> line;
		data += line;
	}

	size = line.length();

	file.close();
}

void cEngineSchematic::Print(void) const
{
	for (uint16_t i = 0U; i < size; i++)
	{
		for (uint16_t j = 0U; j < size; j++)
		{
			std::cout << Get(i, j);
		}
		std::cout << std::endl;
	}
}

uint32_t cEngineSchematic::GetSumOfParts(void)
{
	uint32_t sum = 0U;
	std::list<uint16_t> parts = GetParts();

	for (auto part : parts)
	{
		sum += static_cast<uint32_t>(part);
	}

	return sum;
}

std::list<uint16_t> cEngineSchematic::GetParts(void)
{
	std::list<uint16_t> parts;

	// Backup
	std::string backup = data;

	// Search
	for (uint16_t index = 0U; index < (size * size); index++)
	{
		const char c = data[index];
		if ((c != cEngineSchematic::BlankSpot) && (!isdigit(c)))
		{
			uint16_t i, j;
			GetIndex(index, i, j);
			AskNeighboursForParts(parts, i, j);
		}
	}

	// Restore
	data = backup;

	return parts;
}

void cEngineSchematic::AskNeighboursForParts(std::list<uint16_t>& arg_parts, const uint16_t arg_i, const uint16_t arg_j)
{
	const int8_t offset = 1;
	for (int8_t iOffset = -offset; iOffset <= offset; iOffset++)
	{
		for (int8_t jOffset = -offset; jOffset <= offset; jOffset++)
		{
			int32_t i = arg_i + iOffset;
			int32_t j = arg_j + jOffset;

			bool myPosition = (iOffset == 0) && (jOffset == 0);
			bool outsideBorder = (i < 0) || (i > size) || (j < 0) || (j > size);

			if (myPosition || outsideBorder)
			{
				continue;
			}

			char neighbour = Get(i, j);

			if (isdigit(neighbour))
			{
				uint16_t part = ScanPartNumber(i, j, true);
				arg_parts.push_back(part);
			}
		}
	}
}

uint16_t cEngineSchematic::ScanPartNumber(const uint16_t arg_i, const uint16_t arg_j, const bool arg_pickAndRemove)
{
	std::string partString = "";

	// Center
	const uint16_t centerIndex = GetIndex(arg_i, arg_j);
	partString += data[centerIndex];
	if (arg_pickAndRemove)
	{
		data[centerIndex] = cEngineSchematic::BlankSpot;
	}

	// Prefix
	int32_t j = arg_j - 1;
	while (j >= 0)
	{
		const uint16_t index = GetIndex(arg_i, j);
		const char c = data[index];
		if (!isdigit(c))
		{
			break;
		}

		if (arg_pickAndRemove)
		{
			data[index] = cEngineSchematic::BlankSpot;
		}

		partString = c + partString;
		j--;
	}

	// Sufix
	j = arg_j + 1;
	while (j <= size)
	{
		const uint16_t index = GetIndex(arg_i, j);
		const char c = data[index];
		if (!isdigit(c))
		{
			break;
		}

		if (arg_pickAndRemove)
		{
			data[index] = cEngineSchematic::BlankSpot;
		}

		partString = partString + c;
		j++;
	}

	// Result
	return std::stoi(partString);
}

uint8_t cEngineSchematic::Get(const uint16_t arg_i, const uint16_t arg_j) const
{
	return data[GetIndex(arg_i, arg_j)];
}

uint16_t cEngineSchematic::GetIndex(const uint16_t arg_i, const uint16_t arg_j) const
{
	return arg_i * size + arg_j;
}

void cEngineSchematic::GetIndex(const uint16_t arg_index, uint16_t& arg_i, uint16_t& arg_j) const
{
	arg_i = arg_index / size;
	arg_j = arg_index % size;
}
