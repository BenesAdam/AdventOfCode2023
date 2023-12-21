#include <fstream>
#include <iostream>
#include <unordered_map>

#include "map.hpp"

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
		for (uint32_t i = 0U; i < commands.size(); i++)
		{
			currentNode = currentNode->Step(commands[i]);
			steps++;
			if (currentNode == finish)
			{
				return steps;
			}
		}
	}
}
