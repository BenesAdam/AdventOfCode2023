#pragma once

#include <string>
#include <vector>
#include <fstream>

class cRace
{
public:
	cRace(const uint64_t arg_time, const uint64_t arg_distance);

	static std::vector<cRace> Parse(const std::string& arg_path);
	static uint32_t GetPowerOfPossibleStrategies(const std::vector<cRace>& arg_races);

	uint32_t NumberOfStrategies(void) const;

private:
	static std::vector<uint64_t> ParseNumbers(std::ifstream& arg_file, const std::string& arg_prefix);

	uint64_t BinarySearchStrategy(const uint64_t arg_min, const uint64_t arg_max) const;
	bool IsStrategyPossible(const uint64_t arg_chargingTime) const;

	uint64_t time;
	uint64_t distance;
};
