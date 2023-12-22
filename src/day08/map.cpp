#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

#include "map.hpp"
#include "numeric.hpp"

cMap::cMap(const std::string& arg_path) :
	commands(),
	nodes(),
	start(nullptr),
	finish(nullptr)
{
	std::ifstream file(arg_path);

	if (!file.is_open())
	{
		std::cout << "File is not found." << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string line;
	std::getline(file, line);

	commands = line;

	std::getline(file, line); // empty line

	while (!file.eof())
	{
		std::getline(file, line);
		cNode node(line);
		nodes.push_back(node);
	}

	std::unordered_map<std::string, const cNode*> identifierToNode;
	for (uint16_t i = 0U; i < nodes.size(); i++)
	{
		identifierToNode.emplace(nodes[i].GetIdentifier(), &nodes[i]);
	}

	for (auto& node : nodes)
	{
		node.SearchForNeighbours(identifierToNode);
	}

	start = identifierToNode.at("AAA");
	finish = identifierToNode.at("ZZZ");

	file.close();
}

uint32_t cMap::GetSteps(void) const
{
	uint32_t steps = 0U;
	const cNode* currentNode = start;

	while (true)
	{
		for (char command : commands)
		{
			currentNode = currentNode->Step(command);
			steps++;
			if (currentNode == finish)
			{
				return steps;
			}
		}
	}
}

uint64_t cMap::GetGhostSteps(void) const
{
	std::vector<sParallelBranch> parallelBranches = CreateParallelBranches();	
	ComputeStepsForParallelBranches(parallelBranches);
	return CombineStepsOfParallelBranches(parallelBranches);
}

std::vector<cMap::sParallelBranch> cMap::CreateParallelBranches(void) const
{
	std::vector<sParallelBranch> result;

	for (uint16_t i = 0U; i < nodes.size(); i++)
	{
		const cNode* node = &nodes[i];
		if (node->GetIdentifier().back() == 'A')
		{
			result.push_back({ node, 0U, false });
		}
	}

	return result;
}

void cMap::ComputeStepsForParallelBranches(std::vector<sParallelBranch>& arg_parallelBranches) const
{
	uint16_t commandIndex = 0U;
	uint16_t unfinishedNodes = 0U;
	do
	{
		unfinishedNodes = 0U;
		const char command = commands[commandIndex];

		for (auto& branch : arg_parallelBranches)
		{
			if (branch.complete)
			{
				continue;
			}

			branch.steps++;
			const cNode* nextNode = branch.currentNode->Step(command);
			branch.currentNode = nextNode;

			if (nextNode->GetIdentifier().back() != 'Z')
			{
				unfinishedNodes++;
			}
			else
			{
				branch.complete = true;
			}
		}

		commandIndex = (commandIndex + 1U) % commands.size();
	} while (unfinishedNodes != 0U);
}

uint64_t cMap::CombineStepsOfParallelBranches(std::vector<sParallelBranch>& arg_parallelBranches) const
{
	std::unordered_set<uint64_t> stepsSet;
	for (auto& branch : arg_parallelBranches)
	{
		stepsSet.insert(branch.steps);
	}

	auto stepsIterator = stepsSet.begin();

	const uint64_t first = *stepsIterator;
	const uint64_t second = *(stepsIterator);
	uint64_t steps = nsNumeric::LeastCommonMultiple(first, second);

	for (; stepsIterator != stepsSet.end(); ++stepsIterator)
	{
		steps = nsNumeric::LeastCommonMultiple(steps, *stepsIterator);
	}

	return steps;
}
