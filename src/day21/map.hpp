#pragma once

#include <string>
#include <vector>
#include <set>

#include "position.hpp"

class cMap
{
public:
	cMap(const std::string& arg_path);

	void Compute(const uint32_t arg_steps);

private:
	static const char Start = 'S';
	static const char GardenPlot = '.';
	static const char Rock = '#';
	static const char Visited = 'O';

	void StepFromLocation(const sPosition<int64_t>& arg_position, std::set<sPosition<int64_t>>& arg_positions);

	int64_t width;
	int64_t height;
	std::vector<std::string> data;
	sPosition<int64_t> start;
};
