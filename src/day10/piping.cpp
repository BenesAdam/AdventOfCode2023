#include <iostream>
#include <fstream>

#include "piping.hpp"

const std::vector<std::pair<int8_t, int8_t>> cPiping::directions =
{
	/*    Top */ {-1,  0 },
	/*  Right */ { 0,  1 },
	/* Bottom */ { 1,  0 },
	/*   Left */ { 0, -1 },
};

const std::unordered_map<std::pair<int8_t, int8_t>, std::unordered_set<char>, cPiping::PairHash> cPiping::allowedNeighbours =
{
	/*    Top */ { directions[0], {'S', '|', 'F', '7'}},
	/*  Right */ { directions[1], { 'S', '-', 'J', '7' }},
	/* Bottom */ { directions[2], { 'S', '|', 'J', 'L' }},
	/*   Left */ { directions[3], { 'S', '-', 'L', 'F' }}
};

cPiping::cPiping(const std::string& arg_path) :
	data(),
	size(0U),
	pipes()
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
		data += line;
	}

	size = line.size();

	FindLoop();

	file.close();
}

void cPiping::FindLoop(void)
{
	uint16_t start = GetStart();

	loop.push_back(start);
	pipes.insert(start);

	uint16_t i, j;
	ConvertTo2D(start, i, j);

	bool findNext = true;
	while (findNext)
	{
		findNext = FindNextPipe(i, j);
	}
}

uint16_t cPiping::GetStart(void) const
{
	for (uint16_t i = 0U; i < (size * size); i++)
	{
		const char c = data[i];

		if (c == 'S')
		{
			return i;
		}
	}
}

bool cPiping::FindNextPipe(uint16_t& arg_i, uint16_t& arg_j)
{
	const char centerPiece = data[ConvertToIndex(arg_i, arg_j)];
	for (auto& offset : directions)
	{
		// Check boundaries
		uint16_t neighbourI = arg_i + offset.first;
		uint16_t neighbourJ = arg_j + offset.second;
		if ((neighbourI >= size) || (neighbourJ >= size))
		{
			continue;
		}

		// Pipe already in the loop
		const uint16_t neighbourIndex = ConvertToIndex(neighbourI, neighbourJ);
		if (pipes.count(neighbourIndex) != 0U)
		{
			continue;
		}

		// Neighbour is valid
		const char neighbour = data[neighbourIndex];
		if (!IsNeighbourValid(centerPiece, neighbour, offset))
		{
			continue;
		}

		// Add it to the loop and find next
		if (neighbour != 'S')
		{
			pipes.insert(neighbourIndex);
			loop.push_back(neighbourIndex);

			arg_i = neighbourI;
			arg_j = neighbourJ;

			return true;
		}
	}

	return false;
}

bool cPiping::IsNeighbourValid(const char arg_centerPiece, const char arg_neighbour, const std::pair<int8_t, int8_t>& arg_offset) const
{
	// Check neighbour
	if (allowedNeighbours.at(arg_offset).count(arg_neighbour) == 0U)
	{
		return false;
	}

	// Check center piece
	std::pair<int8_t, int8_t> invertedOffset = { -arg_offset.first, -arg_offset.second };
	if (allowedNeighbours.at(invertedOffset).count(arg_centerPiece) == 0U)
	{
		return false;
	}

	return true;
}

void cPiping::ConvertTo2D(const uint16_t arg_index, uint16_t& arg_i, uint16_t& arg_j) const
{
	arg_i = arg_index / size;
	arg_j = arg_index % size;
}

uint16_t cPiping::ConvertToIndex(const uint16_t arg_i, const uint16_t arg_j) const
{
	return arg_i * size + arg_j;
}

uint32_t cPiping::StepsToMeetAnimal(void)
{
	return  loop.size() / 2U;
}
