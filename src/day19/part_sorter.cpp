#include <iostream>
#include <fstream>

#include "part_sorter.hpp"

cPartSorter::cPartSorter(const std::string& arg_path) :
	workflows(),
	parts()
{
	ParseInput(arg_path);
}

void cPartSorter::ParseInput(const std::string& arg_path)
{
	std::ifstream file(arg_path);

	if (!file.is_open())
	{
		std::cout << "File is not found." << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string line;
	while (!file.eof())
	{
		std::getline(file, line);
		if (line == "")
		{
			break;
		}

		cWorkflow::ParseLine(line, workflows);
	}
	cWorkflow::CompleteWorkflows(workflows);

	while (!file.eof())
	{
		std::getline(file, line);
		sPart part(line);
		parts.push_back(part);
	}

	file.close();
}

bool cPartSorter::IsPartAccepted(sPart& arg_part)
{
	cWorkflow* current = &workflows["in"];

	return current->IsAccepted(arg_part);
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
