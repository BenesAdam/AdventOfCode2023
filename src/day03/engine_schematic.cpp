#include <fstream>
#include <iostream>

#include "engine_schematic.hpp"

//-----------------------------------------------------------------------------
// Constructor with parsing of input file
//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------
// Get parts
//-----------------------------------------------------------------------------

uint32_t cEngineSchematic::GetSumOfParts(void)
{
	uint32_t sum = 0U;
	std::list<uint16_t> parts = GetAllParts();

	for (auto part : parts)
	{
		sum += static_cast<uint32_t>(part);
	}

	return sum;
}

std::list<uint16_t> cEngineSchematic::GetAllParts(void)
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
			SearchAreaForParts(parts, i, j);
		}
	}

	// Restore
	data = backup;

	return parts;
}

void cEngineSchematic::SearchAreaForParts(std::list<uint16_t>& arg_parts, const uint16_t arg_i, const uint16_t arg_j)
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
				uint16_t part = ScanPartNumber(i, j);
				arg_parts.push_back(part);
			}
		}
	}
}

uint16_t cEngineSchematic::ScanPartNumber(const uint16_t arg_i, const uint16_t arg_j)
{
	std::string partString = "";

	// Center
	const uint16_t centerIndex = GetIndex(arg_i, arg_j);
	partString += data[centerIndex];
	data[centerIndex] = cEngineSchematic::BlankSpot;

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

		data[index] = cEngineSchematic::BlankSpot;
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

		data[index] = cEngineSchematic::BlankSpot;
		partString = partString + c;
		j++;
	}

	// Result
	return std::stoi(partString);
}

//-----------------------------------------------------------------------------
// Get sum of gear ratio
//-----------------------------------------------------------------------------

uint32_t cEngineSchematic::GetSumOfGearRatio(void)
{
	uint32_t sum = 0U;

	for (uint16_t index = 0U; index < (size * size); index++)
	{
		const char c = data[index];
		if (c == cEngineSchematic::Gear)
		{
			uint16_t i, j;
			GetIndex(index, i, j);

			sum += GetGearRatio(i, j);
		}
	}

	return sum;
}

uint32_t cEngineSchematic::GetGearRatio(const uint16_t arg_i, const uint16_t arg_j)
{
	uint32_t gearRatio = 0U;

	// Backup
	std::string backup = data;

	// Get adjacent parts
	std::list<uint16_t> parts;
	SearchAreaForParts(parts, arg_i, arg_j);

	// Establish gear ratio only if current position is a gear
	if (parts.size() == cEngineSchematic::GearAdjacentParts)
	{
		for (auto& part : parts)
		{
			gearRatio = (gearRatio == 0U) ? part : (gearRatio * part);
		}
	}

	// Restore
	data = backup;

	return gearRatio;
}

//-----------------------------------------------------------------------------
// Tranformation of index to 2D position and visa versa.
//-----------------------------------------------------------------------------

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
