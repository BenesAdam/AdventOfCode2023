#pragma once

#include <string>
#include <list>
#include <vector>

class cReport
{
public:
	cReport(const std::string& arg_line);

	static std::list<cReport> Parse(const std::string& arg_path);
	static int64_t SumOfExtrapolatedValues(std::list<cReport>& arg_reports, const bool arg_extrapolateBackwards = false);

	int64_t ExtrapolateForwards(void);
	int64_t ExtrapolateBackwards(void);

private:
	void ComputeNextLayers(std::vector<std::vector<int64_t>>& layers, const uint16_t arg_sequenceIndex) const;
	void ComputeSteps(std::vector<std::vector<int64_t>>& layers);

	std::list<int64_t> history;
	std::vector<int64_t> increments;
	std::vector<int64_t> decrements;
};
