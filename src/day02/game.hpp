#pragma once

#include <string>
#include <list>
#include "set.hpp"

class cGame
{
public:
	cGame(const std::string& arg_line);

	uint32_t GetIdentifier(void) const;
	bool IsPossible(const cSet& arg_configuration) const;

private:
	void ParseLine(const std::string& arg_line);

	uint32_t identifier;
	std::list<cSet> sets;
};
