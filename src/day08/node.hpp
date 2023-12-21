#pragma once

#include <string>
#include <unordered_map>

class cNode
{
public:
	cNode(const std::string& arg_line);

	std::string GetIdentifier(void) const;
	void SearchForNeighbours(std::unordered_map<std::string, const cNode*> arg_nodes);
	const cNode* Step(const char arg_command) const;

private:
	std::string identifier;
	std::string strLeft;
	std::string strRight;

	const cNode* left;
	const cNode* right;
};

