#include <iostream>
#include <fstream>
#include <stack>

#include "contraption.hpp"

std::set<std::string> cContraption::visit;

cContraption::cContraption(const std::string& arg_path) :
	width(0U),
	height(0U),
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
		std::getline(file, line);

		std::vector<cCell> row;
		for (auto c : line)
		{
			cCell cell(c);
			row.push_back(cell);
		}

		height++;
		data.push_back(row);
	}

	width = line.size();

	file.close();

	SpreadBeams();
}

void cContraption::SpreadBeams(void)
{
	visit.clear();
	const sPosition<int32_t> dimensions(height, width);

	std::stack<cCell::sBeam> beams;
	beams.push({ cCell::eDirection::RIGHT, {0, 0} });

	while (!beams.empty())
	{
		const cCell::sBeam beam = beams.top();
		beams.pop();

		const std::string label = beam.GetLabel();
		if (visit.count(label) == 0)
		{
			visit.insert(label);
			cCell& cell = data[beam.position.i][beam.position.j];
			cell.ProccessBeam(dimensions, beam, beams);
		}
	}
}

uint16_t cContraption::CountEnergizedTiles(void) const
{
	uint16_t count = 0U;

	for (uint16_t i = 0U; i < height; i++)
	{
		for (uint16_t j = 0U; j < width; j++)
		{
			if (data[i][j].IsEnergized())
			{
				count++;
			}
		}
	}

	return count;
}

void cContraption::Print(void) const
{
	for (uint16_t i = 0U; i < height; i++)
	{
		for (uint16_t j = 0U; j < width; j++)
		{
			std::cout << data[i][j].GetSymbol();
		}

		std::cout << std::endl;
	}
}

void cContraption::Print(const sPosition<int32_t>& arg_position) const
{
	std::cout << " ";
	for (uint16_t j = 0U; j < width; j++)
	{
		std::cout << (arg_position.j == j ? 'v' : ' ');
	}
	std::cout << std::endl;

	for (uint16_t i = 0U; i < height; i++)
	{
		std::cout << (arg_position.i == i ? '>' : ' ');

		for (uint16_t j = 0U; j < width; j++)
		{
			std::cout << data[i][j].GetSymbol();
		}

		std::cout << std::endl;
	}
}
