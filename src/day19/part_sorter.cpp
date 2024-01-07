#include <iostream>

#include "part_sorter.hpp"

cPartSorter::cPartSorter(const std::string& arg_path) :
	workflows(),
	parts()
{
	std::ifstream file(arg_path);

	if (!file.is_open())
	{
		std::cout << "File is not found." << std::endl;
		exit(EXIT_FAILURE);
	}

	ParseWorkflows(file);
	ParseParts(file);

	file.close();
}

void cPartSorter::ParseWorkflows(std::ifstream& arg_file)
{
	std::string line;
	while (!arg_file.eof())
	{
		std::getline(arg_file, line);
		if (line == "")
		{
			break;
		}

		cWorkflow::ParseLine(line, workflows);
	}

	cWorkflow::CompleteWorkflows(workflows);
}

void cPartSorter::ParseParts(std::ifstream& arg_file)
{
	std::string line;
	while (!arg_file.eof())
	{
		std::getline(arg_file, line);
		sPart part(line);
		parts.push_back(part);
	}
}

uint64_t cPartSorter::SumOfAccepted(void)
{
	uint64_t sum = 0U;

	for (auto& part : parts)
	{
		if (IsPartAccepted(part))
		{
			sum += part.GetFinalRating();
		}
	}

	return sum;
}

bool cPartSorter::IsPartAccepted(sPart& arg_part)
{
	return workflows["in"].IsAccepted(arg_part);
}

uint64_t cPartSorter::NumberOfCombinations(void)
{
	return workflows["in"].IntervalOfAccepted(sInterval());
}
