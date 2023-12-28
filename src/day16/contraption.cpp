#include <iostream>
#include <fstream>
#include <stack>

#include "contraption.hpp"

std::set<std::string> cContraption::visit;

cContraption::cContraption(const std::string& arg_path) :
	width(0U),
	height(0U),
	data(),
	energizedTilesUncontrolled(0U),
	energizedTilesControlled(0U)
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

	FireBeams();
}

void cContraption::FireBeams(void)
{
	std::vector<uint16_t> energizedTiles;

	// Fire all beams
	for (uint16_t i = 0U; i < height; i++)
	{
		energizedTiles.push_back(FireBeam({ cCell::eDirection::RIGHT, {i, 0} }));
		energizedTiles.push_back(FireBeam({ cCell::eDirection::LEFT, {i, width - 1} }));
	}

	for (uint16_t j = 0U; j < width; j++)
	{
		energizedTiles.push_back(FireBeam({ cCell::eDirection::BOTTOM, {0, j} }));
		energizedTiles.push_back(FireBeam({ cCell::eDirection::UP, {height - 1, j} }));
	}

	// Process result
	energizedTilesUncontrolled = energizedTiles[0];

	for (auto energized : energizedTiles)
	{
		energizedTilesControlled = std::max(energized, energizedTilesControlled);
	}
}

uint16_t cContraption::FireBeam(const cCell::sBeam arg_beam)
{
	uint16_t visited = 0U;

	std::stack<cCell::sBeam> beams;
	beams.push(arg_beam);

	ResetVisitings();

	while (!beams.empty())
	{
		const cCell::sBeam beam = beams.top();
		beams.pop();

		const std::string label = beam.GetLabel();
		if (visit.count(label) == 0)
		{
			visit.insert(label);
			cCell& cell = data[beam.position.i][beam.position.j];
			visited += cell.ProccessBeam({ height, width }, beam, beams);
		}
	}

	return visited;
}

void cContraption::ResetVisitings(void)
{
	visit.clear();

	for (uint16_t i = 0U; i < height; i++)
	{
		for (uint16_t j = 0U; j < width; j++)
		{
			data[i][j].ResetVoltageLevel();
		}
	}
}

uint16_t cContraption::EnergizedTilesUncontrolled(void) const
{
	return energizedTilesUncontrolled;
}

uint16_t cContraption::EnergizedTilesControlled(void) const
{
	return energizedTilesControlled;
}
