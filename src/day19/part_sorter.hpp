#pragma once

#include <string>
#include <fstream>
#include <map>
#include <list>

#include "workflow.hpp"
#include "part.hpp"

class cPartSorter
{
public:
	cPartSorter(const std::string& arg_path);

	uint64_t SumOfAccepted(void);
	uint64_t NumberOfCombinations(void);

private:
	void ParseWorkflows(std::ifstream& arg_file);
	void ParseParts(std::ifstream& arg_file);

	bool IsPartAccepted(sPart& arg_part);

	std::map<std::string, cWorkflow> workflows;
	std::list<sPart> parts;
};
