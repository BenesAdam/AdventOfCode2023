#pragma once

#include <list>
#include <vector>
#include <string>

#include "position.hpp"

struct cInstraction
{
public:
	cInstraction(const std::string& arg_str, const bool arg_swapped);
	
	static void ParseFile(const std::string& arg_path, std::list<cInstraction>& arg_part1, std::list<cInstraction>& arg_part2);
	static uint64_t ComputeCubicMetersOfLava(const std::list<cInstraction>& arg_instructions);

private:
	void ParseNotSwapped(const char arg_direction, const std::string& arg_steps);
	void ParseSwapped(const std::string& arg_color);

	static uint64_t ShoelaceFormula(const std::list<cInstraction>& arg_instructions);
	void GetNextPosition(const sPosition<int64_t>& arg_current, sPosition<int64_t>& arg_next) const;
	static int64_t CalculateIncrement(const sPosition<int64_t>& arg_currentPosition, const sPosition<int64_t>& arg_nextPosition);
	static uint64_t OuterBoundary(const std::list<cInstraction>& arg_instructions);

	enum eDirection 
	{ 
		RIGHT = 0, 
		DOWN = 1, 
		LEFT = 2, 
		UP = 3, 
	};

	eDirection direction;
	uint32_t steps;
};
