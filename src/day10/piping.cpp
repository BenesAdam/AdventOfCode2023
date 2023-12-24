#include "piping.hpp"

cPiping::cPiping(const std::string& arg_path) :
	matrix(arg_path),
	pipes()
{
	FindLoop();
	FilterOutUnusedPipes();
}

void cPiping::FindLoop(void)
{
	uint32_t start = GetStart();

	loop.push_back(start);
	pipes.insert(start);

	uint16_t i, j;
	matrix.ConvertTo2D(start, i, j);

	bool findNext = true;
	while (findNext)
	{
		findNext = FindNextPipe(i, j);
	}
}

uint32_t cPiping::GetStart(void) const
{
	for (uint32_t i = 0U; i < matrix.Size(); i++)
	{
		const char c = matrix.Get(i);

		if (c == 'S')
		{
			return i;
		}
	}
}

bool cPiping::FindNextPipe(uint16_t& arg_i, uint16_t& arg_j)
{
	const char centerPiece = matrix.Get(arg_i, arg_j);
	for (auto& offset : cMatrix::Directions)
	{
		// Check boundaries
		uint16_t neighbourI = arg_i + offset.first;
		uint16_t neighbourJ = arg_j + offset.second;
		if(!matrix.IsInBoundaries(neighbourI, neighbourJ))
		{
			continue;
		}

		// Pipe already in the loop
		const uint32_t neighbourIndex = matrix.ConvertToIndex(neighbourI, neighbourJ);
		if (pipes.count(neighbourIndex) != 0U)
		{
			continue;
		}

		// Neighbour is valid
		const char neighbour = matrix.Get(neighbourIndex);
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
	if (cMatrix::AllowedNeighbours.at(arg_offset).count(arg_neighbour) == 0U)
	{
		return false;
	}

	// Check center piece
	std::pair<int8_t, int8_t> invertedOffset = { -arg_offset.first, -arg_offset.second };
	if (cMatrix::AllowedNeighbours.at(invertedOffset).count(arg_centerPiece) == 0U)
	{
		return false;
	}

	return true;
}

void cPiping::FilterOutUnusedPipes(void)
{
	for (uint32_t index = 0U; index < matrix.Size(); index++)
	{
		if (pipes.count(index) == 0U)
		{
			matrix.Set(index, '.');
		}
	}
}

uint32_t cPiping::StepsToMeetAnimal(void)
{
	return  loop.size() / 2U;
}

uint32_t cPiping::GetNestSize(void)
{
	cMatrix upscaled = cMatrix::FormUpscaledPiping(matrix);
	upscaled.MarkNest(matrix, loop);

	uint32_t nestSize = 0U;

	for (uint16_t i = 0U; i < matrix.Height(); i++)
	{
		for (uint16_t j = 0U; j < matrix.Width(); j++)
		{
			if (upscaled.Get(i * 2U, j * 2U) == '.')
			{
				nestSize++;
			}
		}
	}

	return nestSize;
}
