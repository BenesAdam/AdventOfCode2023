#include <regex>
#include <sstream>

#include "workflow.hpp"

const std::string cWorkflow::Accepted = "A";
const std::string cWorkflow::Rejected = "R";

cWorkflow::cWorkflow(void) :
	name(""),
	category(sPart::ExtremelyCoolLooking),
	compareGreater(true),
	value(0U),
	positiveStr(""),
	negativeStr(""),
	positive(nullptr),
	negative(nullptr)
{
}

cWorkflow::cWorkflow(const std::string& arg_str) :
	cWorkflow()
{
	std::smatch m;
	std::regex regex("(\\w)(.)(\\d+):(\\w+)");
	std::regex_search(arg_str, m, regex);

	category = sPart::LetterToCategory(m[1].str()[0]);
	compareGreater = (m[2] == ">") ? true : false;
	value = std::stoi(m[3]);
	positiveStr = m[4];
}

void cWorkflow::ParseLine(const std::string& arg_line, std::map<std::string, cWorkflow>& arg_workflows)
{
	// Parse name
	std::smatch m;
	std::regex parseOutName("(\\w+)\\{([^\\}]*)\\}");
	std::regex_search(arg_line, m, parseOutName);

	// Get atomic workflows
	std::vector<cWorkflow> workflows;
	std::string defaultCase;
	ParseRules(m[2], workflows, defaultCase);

	// Assign name and negative
	for (uint16_t i = 0U; i < workflows.size(); i++)
	{
		const std::string newName = (i == 0U) ? m[1] : (m[1].str() + std::to_string(i));
		workflows[i].name = newName;
		if (i != 0U)
		{
			workflows[i - 1U].negativeStr = workflows[i].name;
		}
	}
	workflows[workflows.size() - 1U].negativeStr = defaultCase;

	// Push created workflows to map
	for (auto& workflow : workflows)
	{
		arg_workflows.emplace(workflow.name, workflow);
	}
}

void cWorkflow::CompleteWorkflows(std::map<std::string, cWorkflow>& arg_workflows)
{
	// Push accepted and rejected workflows
	cWorkflow accepted;
	accepted.name = cWorkflow::Accepted;
	arg_workflows.emplace(accepted.name, accepted);

	cWorkflow rejected;
	rejected.name = cWorkflow::Rejected;
	arg_workflows.emplace(rejected.name, rejected);

	// Assign neighbours
	for (auto& workflow : arg_workflows)
	{
		workflow.second.AssignNeighbours(arg_workflows);
	}
}

void cWorkflow::ParseRules(const std::string& arg_rulesStr, std::vector<cWorkflow>& arg_workflows, std::string& arg_defaultCase)
{
	std::stringstream strStream(arg_rulesStr);

	std::string ruleStr;
	while (strStream.good())
	{
		std::getline(strStream, ruleStr, ',');

		if (ruleStr.find(':') != std::string::npos)
		{
			arg_workflows.push_back(cWorkflow(ruleStr));
		}
		else
		{
			arg_defaultCase = ruleStr;
		}
	}
}

void cWorkflow::AssignNeighbours(std::map<std::string, cWorkflow>& arg_workflows)
{
	positive = &arg_workflows[positiveStr];
	negative = &arg_workflows[negativeStr];
}

bool cWorkflow::IsAccepted(const sPart& arg_part) const
{
	const bool positiveBranch = compareGreater ? Greater(arg_part) : Less(arg_part);
	cWorkflow* next = positiveBranch ? positive : negative;

	if (next->name == cWorkflow::Accepted)
	{
		return true;
	}
	else if (next->name == cWorkflow::Rejected)
	{
		return false;
	}
	else
	{
		return next->IsAccepted(arg_part);
	}
}

bool cWorkflow::Less(const sPart& arg_part) const
{
	return arg_part.rating[category] < value;
}

bool cWorkflow::Greater(const sPart& arg_part) const
{
	return arg_part.rating[category] > value;
}
