#pragma once

#include <string>
#include <vector>
#include <fstream>

class cRace
{
public:
	cRace(const uint16_t arg_time, const uint16_t arg_distance);

	static std::vector<cRace> Parse(const std::string& arg_path);
	static uint32_t GetPowerOfPossibleStrategies(const std::vector<cRace>& arg_races);

	uint16_t NumberOfStrategies(void) const;

private:
	static std::vector<uint16_t> ParseNumbers(std::ifstream& arg_file, const std::string& arg_prefix);

	uint16_t BinarySearchStrategy(const uint16_t arg_min, const uint16_t arg_max) const;
	bool IsStrategyPossible(const uint16_t arg_chargingTime) const;

	uint16_t time;
	uint16_t distance;
};
