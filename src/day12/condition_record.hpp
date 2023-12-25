#pragma once

#include <string>
#include <list>
#include <vector>
#include <regex>

class cConditionRecord
{
public:
	cConditionRecord(const std::string& arg_record);

	static void GlobalEnableFolding(const bool arg_enableFolding);
	static std::list<cConditionRecord> ParseFile(const std::string& arg_path);

	static uint64_t NumberOfPossibleWayBruteForce(const std::list<cConditionRecord>& arg_records);
	uint64_t NumberOfPossibleWayBruteForce(void) const;

private:
	void ParseGroups(const std::string& arg_groupsStr);
	std::regex GenerateMatchRegex(const std::string& arg_operational, const std::string& arg_demaged) const;
	uint64_t NumberOfPossibleWayBruteForce(std::string& arg_record, uint32_t arg_questionMarksLeft) const;
	bool RecordIsValid(const std::string& arg_record) const;

	static bool foldingEnabled;

	std::string record;
	std::vector<uint16_t> groups;
	std::regex weakMatchRegex;
	std::regex strongMatchRegex;
};
