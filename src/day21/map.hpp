#pragma once

#include <string>
#include <vector>
#include <set>

#include "position.hpp"

class cMap
{
public:
	cMap(const std::string& arg_path);

	uint32_t GardensWithinReach(const uint32_t arg_steps);
	void Print(std::set<sPosition<uint32_t>>& arg_positions) const;

private:
	static const char Start = 'S';
	static const char GardenPlot = '.';
	static const char Rock = '#';
	static const char Visited = 'O';

	void StepFromLocation(const sPosition<uint32_t>& arg_position, std::set<sPosition<uint32_t>>& arg_positions);

	uint32_t width;
	uint32_t height;
	std::vector<std::string> data;
	sPosition<uint32_t> start;
};
