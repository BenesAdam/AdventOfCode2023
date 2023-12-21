#include <regex>

#include "node.hpp"

cNode::cNode(const std::string& arg_line) :
	identifier(),
	strLeft(),
	strRight(),
	left(nullptr),
	right(nullptr)
{
	std::regex splitIntoGroups("(\\S+) = \\((\\S+?), (\\S+?)\\)");
	std::smatch m;

	std::regex_search(arg_line, m, splitIntoGroups);

	identifier = m[1];
	strLeft = m[2];
	strRight = m[3];
}

std::string cNode::GetIdentifier(void) const
{
	return identifier;
}

void cNode::SearchForNeighbours(std::unordered_map<std::string, const cNode*> arg_nodes)
{
	left = arg_nodes.at(strLeft);
	right = arg_nodes.at(strRight);
}

const cNode* cNode::Step(const char arg_command) const
{
	return (arg_command == 'L') ? left : right;
}
