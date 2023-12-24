#include <iostream>
#include <fstream>

#include "matrix.hpp"

const std::vector<std::pair<int8_t, int8_t>> cMatrix::Directions =
{
	/*    Top */ {-1,  0 },
	/*  Right */ { 0,  1 },
	/* Bottom */ { 1,  0 },
	/*   Left */ { 0, -1 },
};

const std::unordered_map<std::pair<int8_t, int8_t>, std::unordered_set<char>, cMatrix::PairHash> cMatrix::AllowedNeighbours =
{
	/*    Top */ { Directions[0], { 'S', '|', 'F', '7' }},
	/*  Right */ { Directions[1], { 'S', '-', 'J', '7' }},
	/* Bottom */ { Directions[2], { 'S', '|', 'J', 'L' }},
	/*   Left */ { Directions[3], { 'S', '-', 'L', 'F' }}
};

cMatrix::cMatrix(void) :
	data(),
	width(0U),
	height(0U)
{
}

cMatrix::cMatrix(const std::string& arg_path) :
	cMatrix()
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
		height++;

		std::getline(file, line);
		data += line;
	}

	width = line.size();

	file.close();
}

uint32_t cMatrix::Size(void) const
{
	return width * height;
}

uint16_t cMatrix::Width(void) const
{
	return width;
}

uint16_t cMatrix::Height(void) const
{
	return height;
}

char cMatrix::Get(const uint32_t arg_index) const
{
	return data[arg_index];
}

char cMatrix::Get(const uint16_t arg_i, const uint16_t arg_j) const
{
	return data[ConvertToIndex(arg_i, arg_j)];
}

void cMatrix::Set(const uint32_t arg_index, const char arg_value)
{
	data[arg_index] = arg_value;
}

void cMatrix::ConvertTo2D(const uint32_t arg_index, uint16_t& arg_i, uint16_t& arg_j) const
{
	arg_i = arg_index / width;
	arg_j = arg_index % width;
}

uint32_t cMatrix::ConvertToIndex(const uint16_t arg_i, const uint16_t arg_j) const
{
	return arg_i * width + arg_j;
}

bool cMatrix::IsInBoundaries(const uint16_t arg_i, const uint16_t arg_j) const
{
	return ((arg_i < height) && (arg_j < width));
}

void cMatrix::Print(void) const
{
	for (uint16_t i = 0U; i < height; i++)
	{
		for (uint16_t j = 0U; j < width; j++)
		{
			const uint32_t index = ConvertToIndex(i, j);
			std::cout << Get(index);
		}
		std::cout << std::endl;
	}
}

cMatrix cMatrix::FormUpscaledPiping(const cMatrix& arg_matrix)
{
	cMatrix upscaled;

	upscaled.width = arg_matrix.width * 2U;
	upscaled.height = arg_matrix.height * 2U;

	// Transfer original characters
	for (uint16_t i = 0U; i < arg_matrix.height; i++)
	{
		for (uint16_t j = 0U; j < arg_matrix.width; j++)
		{
			const char c = arg_matrix.Get(i, j);
			upscaled.data += c;
			upscaled.data += '.';
		}
		upscaled.data += std::string(upscaled.width, '.');
	}

	return upscaled;
}

void cMatrix::MarkNest(const cMatrix& arg_originalMatrix, const std::vector<uint32_t> arg_loop)
{
	// Fill gaps
	for (uint16_t i = 0U; i < arg_loop.size(); i++)
	{
		std::pair<uint16_t, uint16_t> currentPosition;
		std::pair<uint16_t, uint16_t> nextPosition;

		arg_originalMatrix.ConvertTo2D(arg_loop[i], currentPosition.first, currentPosition.second);
		arg_originalMatrix.ConvertTo2D(arg_loop[(i + 1U) % arg_loop.size()], nextPosition.first, nextPosition.second);

		currentPosition.first *= 2U;
		nextPosition.first *= 2U;
		currentPosition.second *= 2U;
		nextPosition.second *= 2U;

		std::pair<uint16_t, uint16_t> center =
		{
			(currentPosition.first + nextPosition.first) / 2U,
			(currentPosition.second + nextPosition.second) / 2U
		};

		uint32_t centerIndex = ConvertToIndex(center.first, center.second);
		Set(centerIndex, '#');
	}

	SpreadVoid();
}

void cMatrix::SpreadVoid(void)
{
	std::stack<uint32_t> stack;

	// Horizontal seeds
	for (uint16_t i = 0U; i < height; i++)
	{
		stack.push(ConvertToIndex(i, 0U));
		stack.push(ConvertToIndex(i, width - 1U));
	}

	// Vertical seeds
	for (uint16_t j = 0U; j < width; j++)
	{
		stack.push(ConvertToIndex(0U, j));
		stack.push(ConvertToIndex(height - 1U, j));
	}


	while (!stack.empty())
	{
		uint32_t index = stack.top();
		stack.pop();

		SpreadVoid(index, stack);
	}
}

void cMatrix::SpreadVoid(const uint32_t arg_index, std::stack<uint32_t>& arg_stack)
{
	uint16_t i, j;
	ConvertTo2D(arg_index, i, j);

	// Check boundaries
	if (!IsInBoundaries(i, j))
	{
		return;
	}

	// Check character
	const char c = Get(arg_index);
	if (c != '.')
	{
		return;
	}

	// Make it void
	Set(arg_index, ' ');

	// Spread void to neighbours
	for (auto& offset : Directions)
	{
		const uint16_t nextI = i + offset.first;
		const uint16_t nextJ = j + offset.second;
		uint32_t nextIndex = ConvertToIndex(nextI, nextJ);
		arg_stack.push(nextIndex);
	}
}
