#include <iostream>
#include <sstream>

#include "race.hpp"

cRace::cRace(const uint64_t arg_time, const uint64_t arg_distance) :
	time(arg_time),
	distance(arg_distance)
{
}

std::vector<cRace> cRace::Parse(const std::string& arg_path)
{
	std::vector<cRace> races;

	std::ifstream file(arg_path);
	if (!file.is_open())
	{
		std::cout << "File is not found." << std::endl;
		exit(EXIT_FAILURE);
	}

	std::vector<uint64_t> times = ParseNumbers(file, "Time:");
	std::vector<uint64_t> distances = ParseNumbers(file, "Distance:");

	for (uint8_t i = 0U; i < times.size(); i++)
	{
		cRace race(times[i], distances[i]);
		races.push_back(race);
	}

	return races;
}

std::vector<uint64_t> cRace::ParseNumbers(std::ifstream& arg_file, const std::string& arg_prefix)
{
	std::vector<uint64_t> numbers;

	// Get line
	std::string line;
	std::getline(arg_file, line);
	line = line.substr(arg_prefix.length());

	// Convert string to vector on numbers
	std::stringstream ss(line);
	uint64_t number;
	while (ss >> number)
	{
		numbers.push_back(number);
	}

	return numbers;
}

uint32_t cRace::GetPowerOfPossibleStrategies(const std::vector<cRace>& arg_races)
{
	uint32_t result = 1U;

	for (auto& race : arg_races)
	{
		result *= race.NumberOfStrategies();
	}

	return result;
}

uint32_t cRace::NumberOfStrategies(void) const
{
	uint32_t result = 0U;

	// Find center time
	uint64_t centerWay = BinarySearchStrategy(1U, time - 1U);

	if (centerWay != 0U)
	{
		result++;

		// Search for shorter time
		for (uint64_t i = (centerWay - 1U); i >= 1; i--)
		{
			if (!IsStrategyPossible(i))
			{
				break;
			}

			result++;
		}

		// Search for longer time
		for (uint64_t i = (centerWay + 1U); i < time; i++)
		{
			if (!IsStrategyPossible(i))
			{
				break;
			}

			result++;
		}
	}

	return result;
}

uint64_t cRace::BinarySearchStrategy(const uint64_t arg_min, const uint64_t arg_max) const
{
	if (arg_min > arg_max)
	{
		return 0U;
	}

	uint64_t center = (arg_max + arg_min) / 2U;

	if (IsStrategyPossible(center))
	{
		return center;
	}

	uint64_t shorterTime = BinarySearchStrategy(arg_min, center - 1U);
	if (shorterTime != 0U)
	{
		return shorterTime;
	}

	uint64_t longerTime = BinarySearchStrategy(center + 1U, arg_max);
	if (longerTime != 0U)
	{
		return longerTime;
	}

	return 0U;
}

bool cRace::IsStrategyPossible(const uint64_t arg_chargingTime) const
{
	const uint64_t achievedDistance = (time - arg_chargingTime) * arg_chargingTime;
	return achievedDistance > distance;
}
