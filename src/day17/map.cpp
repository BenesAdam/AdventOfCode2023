#include <iostream>
#include <fstream>
#include <queue>
#include <set>

#include "map.hpp"
#include "state.hpp"

cMap::cMap(const std::string& arg_path) :
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
		data.push_back(line);
		height++;
	}

	width = line.size();

	file.close();
}

uint32_t cMap::GetLeastHeatLoss(const uint8_t arg_minSteps, const uint8_t arg_maxSteps)
{
	sPosition<uint16_t> end(height - 1U, width - 1U);

	std::priority_queue<sState, std::vector<sState>, std::greater<sState>> queue;
	std::set<std::string> seen;

	queue.push(sState(0U, { 0U, 0U }, sState::RIGHT, 0U));
	queue.push(sState(0U, { 0U, 0U }, sState::DOWN, 0U));

	static const sPosition<int8_t> offsets[] = {
		/*    UP */ {-1, 0},
		/* RIGHT */ {0, 1},
		/*  DOWN */ {1, 0},
		/*  LEFT */ {0, -1}
	};

	while (!queue.empty())
	{
		sState state = queue.top();
		queue.pop();

		// end reached
		if ((state.position == end) && (state.steps >= arg_minSteps))
		{
			return state.score;
		}

		// already visited
		if (seen.find(state.GetLabelNoScore()) != seen.end())
		{
			continue;
		}
		seen.insert(state.GetLabelNoScore());

		// for every neighbour
		for (uint8_t i = 0U; i < 4U; i++)
		{
			// moving backwards
			if (((i + 2U) % 4U) == state.direction)
			{
				continue;
			}

			const sPosition<int8_t>& offset = offsets[i];
			const sPosition<uint16_t> position(state.position.i + offset.i, state.position.j + offset.j);

			// boundary check
			if ((position.i >= height) || (position.j >= width))
			{
				continue;
			}

			// steps check
			const bool stepsGood = (state.direction == i) ? (state.steps < arg_maxSteps) : (state.steps >= arg_minSteps);
			if (!stepsGood)
			{
				continue;
			}

			const uint32_t score = state.score + (data[position.i][position.j] - '0');
			const uint8_t steps = (state.direction == i) ? (state.steps + 1U) : 1U;

			queue.push(sState(score, position, static_cast<sState::eDirection>(i), steps));
		}
	}

	return 0U;
}
