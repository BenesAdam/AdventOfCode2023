#pragma once

#include <fstream>
#include <vector>

class cMap
{
public:
	cMap(std::ifstream& arg_file);

	uint64_t operator[] (uint64_t arg_source) const;

private:
	struct sRange
	{
		uint64_t sourceStart;
		uint64_t destinationStart;
		uint64_t length;

		sRange(const uint64_t arg_sourceStart, const uint64_t arg_destinationStart, const uint64_t arg_length);
		bool Contains(const uint64_t arg_source) const;
		uint64_t GetDestination(const uint64_t arg_source) const;
		static bool Sort(const sRange& a, const sRange& b);
	};

	std::vector<sRange> ranges;

};
