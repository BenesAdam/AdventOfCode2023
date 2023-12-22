#pragma once

#include <string>
#include <vector>

#include "node.hpp"

class cMap
{
public:
	cMap(const std::string& arg_path);

	uint32_t GetSteps(void) const;
	uint64_t GetGhostSteps(void) const;

private:
	struct sParallelBranch
	{
		const cNode* currentNode;
		uint64_t steps;
		bool complete;
	};

	std::vector<sParallelBranch> CreateParallelBranches(void) const;
	void ComputeStepsForParallelBranches(std::vector<sParallelBranch>& arg_parallelBranches) const;
	uint64_t CombineStepsOfParallelBranches(std::vector<sParallelBranch>& arg_parallelBranches) const;

	std::string commands;
	std::vector<cNode> nodes;
	const cNode* start;
	const cNode* finish;
};

