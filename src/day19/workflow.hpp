#pragma once

#include <string>
#include <list>
#include <map>
#include <vector>

#include "part.hpp"

class cWorkflow
{
public:
	static const std::string Accepted;
	static const std::string Rejected;
	
	cWorkflow(void);
	cWorkflow(const std::string& arg_str);

	static void ParseLine(const std::string& arg_line, std::map<std::string, cWorkflow>& arg_workflows);
	static void CompleteWorkflows(std::map<std::string, cWorkflow>& arg_workflows);

	bool IsAccepted(const sPart& arg_part) const;

private:
	static void ParseRules(const std::string& arg_rulesStr, std::vector<cWorkflow>& arg_workflows, std::string& arg_defaultCase);
	void AssignNeighbours(std::map<std::string, cWorkflow>& arg_workflows);

	bool Less(const sPart& arg_part) const;
	bool Greater(const sPart& arg_part) const;

	std::string name;

	sPart::eCategory category;
	bool compareGreater;
	uint16_t value;

	std::string positiveStr;
	std::string negativeStr;

	cWorkflow* positive;
	cWorkflow* negative;
};
