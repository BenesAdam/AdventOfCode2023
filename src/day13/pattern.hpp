#pragma once

#include <string>
#include <fstream>
#include <list>
#include <vector>

#include "position.hpp"

class cPattern
{
public:
	cPattern(void);
	cPattern(std::ifstream& arg_file);

	static std::list<cPattern> ParseFile(const std::string& arg_path);
	static uint32_t ReflectionSummarization(std::list<cPattern>& arg_patterns);

	uint32_t ReflectionSummarization(void);
	uint16_t FindVerticalReflection(void);
	uint16_t FindHorizontalReflection(void);

private:
	cPattern GetRotated(void) const;
	uint16_t FindHorizontalReflection(const uint16_t arg_firstRowIndex, std::vector<std::string>& arg_rows,
		sPosition<uint16_t>& arg_smudge, const uint16_t arg_notSmudgedSolution);
	bool CheckHorizontalReflection(std::vector<std::string>& arg_rows, const uint16_t arg_firstRowIndex,
		const uint16_t arg_secondRowIndex, sPosition<uint16_t>& arg_smudge) const;
	bool ExactlyOneSmudge(const std::string& arg_first, const std::string& arg_second, sPosition<uint16_t>& arg_smudge) const;

	sPosition<uint16_t> GetPosition(const uint32_t arg_index) const;
	uint32_t GetIndex(const sPosition<uint16_t>& arg_position) const;
	uint32_t GetIndex(const uint32_t arg_i, const uint32_t arg_j) const;
	char Get(const uint32_t arg_index) const;
	char Get(const sPosition<uint16_t>& arg_position) const;
	char Get(const uint32_t arg_i, const uint32_t arg_j) const;

	uint16_t width;
	uint16_t height;
	std::string data;
};
