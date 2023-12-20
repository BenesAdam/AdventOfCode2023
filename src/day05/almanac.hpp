#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <list>

#include "map.hpp"

class cAlmanac
{
public:
	cAlmanac(const std::string& arg_path);

	uint64_t GetLocation(const uint64_t arg_seed) const;
	uint64_t GetMinimalLocation(const bool arg_seedsAreRanges = false) const;

private:
	void ParseSeeds(std::ifstream& arg_file);
	void ParseMaps(std::ifstream& arg_file);

	std::vector<uint64_t> seeds;
	std::list<cMap> maps;
};
