#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>

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

uint64_t cConditionRecord::NumberOfPossibleWay(const std::list<cConditionRecord>& arg_records)
{
	uint64_t sum = 0U;

	auto start = std::chrono::high_resolution_clock::now();

	for (auto& record : arg_records)
	{
		const uint64_t possibilities = record.NumberOfPossibleWay();
		sum += possibilities;
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto runtime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	std::cout << "(" << runtime.count() << "ms) ";

	return sum;
}

uint64_t cConditionRecord::NumberOfPossibleWay(void) const
{
	std::unordered_map<std::string, uint64_t> cache;
	return NumberOfPossibleWay(0U, 0U, 0U, cache);
}

uint64_t cConditionRecord::NumberOfPossibleWay(uint16_t arg_recordIndex, uint16_t arg_groupIndex, uint16_t arg_springsConsumed,
	std::unordered_map<std::string, uint64_t>& arg_cache) const
{
	// Check group index
	const bool allGroupsConsumed = arg_groupIndex == groups.size();
	const bool lastGroupConsumed = (arg_groupIndex == (groups.size() - 1U)) && (groups[arg_groupIndex] == arg_springsConsumed);
	if (allGroupsConsumed || lastGroupConsumed)
	{
		// Check that all springs was consumed
		const bool allSpringConsumed = arg_recordIndex == record.size();
		const bool noSpringsLeft = (record.find("#", arg_recordIndex) == std::string::npos);
		return (allSpringConsumed || noSpringsLeft) ? 1U : 0U;
	}

	// Run out of springs and some groups left
	if (arg_recordIndex == record.size())
	{
		return 0U;
	}

	// Check cache
	std::string key = std::to_string(arg_recordIndex) + "-" + std::to_string(arg_groupIndex) + "-" + std::to_string(arg_springsConsumed);
	if (arg_cache.find(key) != arg_cache.end())
	{
		return arg_cache[key];
	}

	uint64_t result = 0U;
	const char currentSpring = record[arg_recordIndex];
	const bool currentGroupDone = (groups[arg_groupIndex] == arg_springsConsumed) && ((currentSpring == '.') || (currentSpring == '?'));
	
	/* Group is fully consumed */
	if (currentGroupDone)
	{
		result = NumberOfPossibleWay(arg_recordIndex + 1U, arg_groupIndex + 1U, 0U, arg_cache);
	}
	/* First spring in group */
	else if (arg_springsConsumed == 0U)
	{
		/* Consume demaged spring */
		if (currentSpring == '#')
		{
			result = NumberOfPossibleWay(arg_recordIndex + 1U, arg_groupIndex, 1U, arg_cache);
		}
		/* Consume operational spring */
		else if (currentSpring == '.')
		{
			result = NumberOfPossibleWay(arg_recordIndex + 1U, arg_groupIndex, 0U, arg_cache);
		}
		/* Consume unknown spring */
		else /* (currentSpring == '?') */
		{
			result += NumberOfPossibleWay(arg_recordIndex + 1U, arg_groupIndex, 1U, arg_cache);
			result += NumberOfPossibleWay(arg_recordIndex + 1U, arg_groupIndex, 0U, arg_cache);
		}
	}
	/* Next spring in group */
	else if ((currentSpring == '#') || (currentSpring == '?'))
	{
			result = NumberOfPossibleWay(arg_recordIndex + 1U, arg_groupIndex, arg_springsConsumed + 1U, arg_cache);
	}

	// Cache and return result
	arg_cache[key] = result;
	return result;
}
