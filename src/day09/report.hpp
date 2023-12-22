#pragma once

#include <string>
#include <list>
#include <vector>

class cReport
{
public:
	cReport(const std::string& arg_line);

	static std::list<cReport> Parse(const std::string& arg_path);
	static int64_t SumOfExtrapolatedValues(std::list<cReport>& arg_reports);

	int64_t ComputeNextValue(void);

private:
	void ComputeNextLayers(std::vector<std::vector<int64_t>>& layers, const uint16_t arg_sequenceIndex) const;
	void ComputeIncrements(std::vector<std::vector<int64_t>>& layers);

	std::vector<int64_t> history;
	std::vector<int64_t> increments;
};
