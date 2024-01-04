#pragma once

#include <string>
#include <map>
#include <list>

#include "workflow.hpp"
#include "part.hpp"

class cPartSorter
{
public:
	cPartSorter(const std::string& arg_path);

	uint64_t SumOfAccepted(void);

private:
	void ParseInput(const std::string& arg_path);
	bool IsPartAccepted(sPart& arg_part);

	std::map<std::string, cWorkflow> workflows;
	std::list<sPart> parts;
};
