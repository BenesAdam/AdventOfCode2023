#include "game.hpp"
#include <regex>
#include <iostream>
#include <sstream>

cGame::cGame(const std::string& arg_line) :
	identifier(0U),
	sets()
{
	ParseLine(arg_line);
}

void cGame::ParseLine(const std::string& arg_line)
{
	// Split
	std::smatch m;
	std::regex regexIdentifierAndSets("Game (\\d*):(.*)");
	std::regex_search(arg_line, m, regexIdentifierAndSets);

	// Set ID
	this->identifier = stoi(m[1].str());

	// Configure sets
	std::string stringSets = m[2].str();

	//   preproccess of string input
	stringSets = std::regex_replace(stringSets, std::regex(",| "), "");
	stringSets = std::regex_replace(stringSets, std::regex("red"), "R");
	stringSets = std::regex_replace(stringSets, std::regex("green"), "G");
	stringSets = std::regex_replace(stringSets, std::regex("blue"), "B");

	//   create and insert set into list of sets
	std::istringstream inputStream(stringSets);
	std::string stringSet;
	while (std::getline(inputStream, stringSet, ';'))
	{
		cSet set(stringSet);
		sets.push_back(set);
	}
}

uint32_t cGame::GetIdentifier(void) const
{
	return identifier;
}

bool cGame::IsPossible(const cSet& arg_configuration) const
{
	for (auto& set : sets)
	{
		if (!set.IsPossible(arg_configuration))
		{
			return false;
		}
	}

	return true;
}
