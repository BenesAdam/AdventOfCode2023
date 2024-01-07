#pragma once

#include <string>
#include <list>
#include <map>
#include <vector>

#include "part.hpp"

class cWorkflow
{
public:
	cWorkflow(void);
	cWorkflow(const std::string& arg_str);

	static void ParseLine(const std::string& arg_line, std::map<std::string, cWorkflow>& arg_workflows);
	static void CompleteWorkflows(std::map<std::string, cWorkflow>& arg_workflows);

	bool IsAccepted(const sPart& arg_part) const;
	uint64_t IntervalOfAccepted(const sInterval& arg_interval) const;

	static const std::string Accepted;
	static const std::string Rejected;

private:
	static void ParseRules(const std::string& arg_rulesStr, std::vector<cWorkflow>& arg_workflows, std::string& arg_defaultCase);
	void AssignNeighbours(std::map<std::string, cWorkflow>& arg_workflows);

	sInterval TrimIntervalPositiveBranch(sInterval arg_interval) const;
	sInterval TrimIntervalNegativeBranch(sInterval arg_interval) const;

	bool Less(const sPart& arg_part) const;
	bool Greater(const sPart& arg_part) const;

	enum eComparator
	{
		LESS, GREATER
	};

	std::string name;
	sPart::eCategory category;
	eComparator comparator;
	uint16_t value;
	std::string positiveStr;
	std::string negativeStr;
	cWorkflow* positive;
	cWorkflow* negative;
};
