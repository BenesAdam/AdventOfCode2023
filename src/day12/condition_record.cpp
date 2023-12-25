#include <fstream>
#include <iostream>
#include <sstream>

#include "condition_record.hpp"

bool cConditionRecord::foldingEnabled = false;

void cConditionRecord::GlobalEnableFolding(const bool arg_enableFolding)
{
	foldingEnabled = arg_enableFolding;
}

std::list<cConditionRecord> cConditionRecord::ParseFile(const std::string& arg_path)
{
	std::ifstream file(arg_path);

	if (!file.is_open())
	{
		std::cout << "File is not found." << std::endl;
		exit(EXIT_FAILURE);
	}

	std::list<cConditionRecord> records;

	std::string line;
	while (!file.eof())
	{
		std::getline(file, line);
		cConditionRecord record(line);
		records.push_back(record);
	}

	file.close();

	return records;
}

cConditionRecord::cConditionRecord(const std::string& arg_record) :
	record(),
	groups()
{
	uint32_t spaceIndex = arg_record.find(' ');
	record = arg_record.substr(0U, spaceIndex);

	if (foldingEnabled)
	{
		const std::string addition = "?" + record;
		for (uint8_t i = 0U; i < 4U; i++)
		{
			record += addition;
		}
	}

	ParseGroups(arg_record.substr(spaceIndex + 1U));
}

void cConditionRecord::ParseGroups(const std::string& arg_groupsStr)
{
	const auto target = std::regex{ "," };
	std::string groupsStr = std::regex_replace(arg_groupsStr, target, " ");

	std::stringstream ss(groupsStr);
	uint16_t group;
	while (ss >> group)
	{
		groups.push_back(group);
	}

	strongMatchRegex = GenerateMatchRegex(".", "#");
	weakMatchRegex = GenerateMatchRegex(".\\?", "#\\?");

	if (foldingEnabled)
	{
		std::vector<uint16_t> groupsOriginal = groups;

		for (uint16_t i = 0U; i < 4U; i++)
		{
			for (auto item : groupsOriginal)
			{
				groups.push_back(item);
			}
		}
	}
}

std::regex cConditionRecord::GenerateMatchRegex(const std::string& arg_operational, const std::string& arg_demaged) const
{
	std::string operational = "[" + arg_operational + "]";
	std::string demaged = "[" + arg_demaged + "]";

	std::string match = operational + "*?";
	for (auto group : groups)
	{
		match += demaged + "{" + std::to_string(group) + "}";
		match += operational + "+";
	}

	match.pop_back();
	match += "*";

	if(foldingEnabled)
	{
		match = "(?:" + match + "){5}";
	}

	return std::regex(match);
}


uint64_t cConditionRecord::NumberOfPossibleWayBruteForce(const std::list<cConditionRecord>& arg_records)
{
	uint64_t sum = 0U;

	for (auto& record : arg_records)
	{
		const uint64_t possibilities = record.NumberOfPossibleWayBruteForce();
		sum += possibilities;
	}

	return sum;
}

uint64_t cConditionRecord::NumberOfPossibleWayBruteForce(void) const
{
	// Number of question marks
	uint32_t questionMarks = 0U;
	for (auto c : record)
	{
		if (c == '?')
		{
			questionMarks++;
		}
	}

	// Start recursion
	std::string recordCpy = record;
	return NumberOfPossibleWayBruteForce(recordCpy, questionMarks);
}

uint64_t cConditionRecord::NumberOfPossibleWayBruteForce(std::string& arg_record, uint32_t arg_questionMarksLeft) const
{
	if (!std::regex_match(arg_record, weakMatchRegex))
	{
		return 0U;
	}

	if (arg_questionMarksLeft == 0U)
	{
		return (std::regex_match(arg_record, strongMatchRegex)) ? 1U : 0U;
	}

	uint64_t sum = 0U;
	uint32_t questionMarkIndex = arg_record.find('?');

	arg_record[questionMarkIndex] = '#';
	sum += NumberOfPossibleWayBruteForce(arg_record, arg_questionMarksLeft - 1U);

	arg_record[questionMarkIndex] = '.';
	sum += NumberOfPossibleWayBruteForce(arg_record, arg_questionMarksLeft - 1U);

	arg_record[questionMarkIndex] = '?';
	return sum;
}

bool cConditionRecord::RecordIsValid(const std::string& arg_record) const
{
	uint32_t groupIndex = 0U;
	
	uint32_t workingInRow = 0U;
	std::string record = arg_record + ".";
	for (auto c : record)
	{
		if ((c == '.') && (workingInRow != 0U))
		{
			if (groupIndex >= groups.size())
			{
				return false;
			}

			if (workingInRow != groups[groupIndex])
			{
				return false;
			}

			groupIndex++;
			workingInRow = 0U;
		}

		if (c == '#')
		{
			workingInRow++;
		}
	}

	return groupIndex == groups.size();
}
