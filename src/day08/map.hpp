#pragma once

#include <string>
#include <vector>

#include "node.hpp"

class cMap
{
public:
	cMap(const std::string& arg_path);

	uint32_t GetSteps(void) const;

private:
	std::string commands;
	std::vector<cNode> nodes;
	const cNode* start;
	const cNode* finish;
};

