#pragma once

#include <string>
#include <list>
#include <vector>
#include <regex>
#include <unordered_map>

class cConditionRecord
{
public:
	cConditionRecord(const std::string& arg_record);

	static void GlobalEnableFolding(const bool arg_enableFolding);
	static std::list<cConditionRecord> ParseFile(const std::string& arg_path);

	static uint64_t NumberOfPossibleWay(const std::list<cConditionRecord>& arg_records);
	uint64_t NumberOfPossibleWay(void) const;

private:
	void ParseGroups(const std::string& arg_groupsStr);
	uint64_t NumberOfPossibleWay(uint16_t arg_recordIndex, uint16_t arg_groupIndex, uint16_t arg_springsConsumed,
		std::unordered_map<std::string, uint64_t>& arg_cache) const;

	static bool foldingEnabled;

	std::string record;
	std::vector<uint16_t> groups;
};
