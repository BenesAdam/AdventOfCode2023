#include <regex>
#include <sstream>

#include "workflow.hpp"

const std::string cWorkflow::Accepted = "A";
const std::string cWorkflow::Rejected = "R";

cWorkflow::cWorkflow(void) :
	name(""),
	category(sPart::ExtremelyCoolLooking),
	comparator(LESS),
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
	comparator = (m[2] == '>') ? GREATER : LESS;
	value = std::stoi(m[3]);
	positiveStr = m[4];
}

void cWorkflow::ParseLine(const std::string& arg_line, std::map<std::string, cWorkflow>& arg_workflows)
{
	// Parse name
	std::smatch m;
	std::regex parseOutName("(\\w+)\\{([^\\}]*)\\}");
	std::regex_search(arg_line, m, parseOutName);

	// Get atomic workflows with positive string
	std::vector<cWorkflow> workflows;
	std::string defaultCase;
	ParseRules(m[2], workflows, defaultCase);

	// Assign name and negative string
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
	const bool positiveBranch = (comparator == GREATER) ? Greater(arg_part) : Less(arg_part);
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

uint64_t cWorkflow::IntervalOfAccepted(const sInterval& arg_interval) const
{
	if (name == Rejected)
	{
		return 0U;
	}

	if (name == Accepted)
	{
		return arg_interval.CalculateProduct();
	}

	uint64_t result = 0U;

	// Positive branch
	const sInterval positiveInterval = TrimIntervalPositiveBranch(arg_interval);
	if (positiveInterval.min.rating[category] <= positiveInterval.max.rating[category])
	{
		result += positive->IntervalOfAccepted(positiveInterval);
	}

	// Negative branch
	const sInterval negativeInterval = TrimIntervalNegativeBranch(arg_interval);
	if (negativeInterval.min.rating[category] <= negativeInterval.max.rating[category])
	{
		result += negative->IntervalOfAccepted(negativeInterval);
	}

	return result;
}

sInterval cWorkflow::TrimIntervalPositiveBranch(sInterval arg_interval) const
{
	if (comparator == GREATER)
	{
		arg_interval.min.rating[category] = std::max(arg_interval.min.rating[category], static_cast<uint16_t>(value + 1U));
	}
	else
	{
		arg_interval.max.rating[category] = std::min(arg_interval.max.rating[category], static_cast<uint16_t>(value - 1U));
	}

	return arg_interval;
}

sInterval cWorkflow::TrimIntervalNegativeBranch(sInterval arg_interval) const
{
	if (comparator == GREATER)
	{
		arg_interval.max.rating[category] = std::min(arg_interval.max.rating[category], value);
	}
	else
	{
		arg_interval.min.rating[category] = std::max(arg_interval.min.rating[category], value);
	}

	return arg_interval;
}

bool cWorkflow::Less(const sPart& arg_part) const
{
	return arg_part.rating[category] < value;
}

bool cWorkflow::Greater(const sPart& arg_part) const
{
	return arg_part.rating[category] > value;
}
