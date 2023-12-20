#include <iostream>
#include <sstream>

#include "almanac.hpp"

cAlmanac::cAlmanac(const std::string& arg_path) :
	seeds(),
	maps()
{
	std::ifstream file(arg_path);

	if (!file.is_open())
	{
		std::cout << "File is not found." << std::endl;
		exit(EXIT_FAILURE);
	}

	ParseSeeds(file);

	ParseMaps(file);

	file.close();
}

void cAlmanac::ParseSeeds(std::ifstream& arg_file)
{
	std::string line;
	std::getline(arg_file, line);

	std::string seedsString = line.substr(line.find(':') + 1U);
	std::stringstream ss(seedsString);
	uint64_t seed;
	while (ss >> seed)
	{
		seeds.push_back(seed);
	}

	std::getline(arg_file, line); // process empty line
}

void cAlmanac::ParseMaps(std::ifstream& arg_file)
{
	std::string line;
	while (!arg_file.eof())
	{
		std::getline(arg_file, line); // process map's title

		cMap map(arg_file);
		maps.push_back(map);
	}
}

uint64_t cAlmanac::GetLocation(const uint64_t arg_seed) const
{
	uint64_t value = arg_seed;

	for (auto& map : maps)
	{
		value = map[value];
	}

	return value;
}

uint64_t cAlmanac::GetMinimalLocation(void) const
{
	uint64_t minimum = UINT64_MAX;

	for (uint64_t seed : seeds)
	{
		minimum = std::min(minimum, GetLocation(seed));
	}

	return minimum;
}
