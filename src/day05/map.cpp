#include <string>
#include <regex>

#include "map.hpp"

//-----------------------------------------------------------------------------
// Range
//-----------------------------------------------------------------------------
cMap::sRange::sRange(const uint64_t arg_sourceStart, const uint64_t arg_destinationStart, const uint64_t arg_length) :
	sourceStart(arg_sourceStart),
	destinationStart(arg_destinationStart),
	length(arg_length)
{
}

bool cMap::sRange::Contains(const uint64_t arg_source) const
{
	return (sourceStart <= arg_source) && (arg_source <= (sourceStart + length - 1U));
}

uint64_t cMap::sRange::GetDestination(const uint64_t arg_source) const
{
	int64_t offset = destinationStart - sourceStart;
	return arg_source + offset;
}

bool cMap::sRange::Sort(const sRange& a, const sRange& b)
{
	return a.sourceStart < b.sourceStart;
}

//-----------------------------------------------------------------------------
// Map
//-----------------------------------------------------------------------------
cMap::cMap(std::ifstream& arg_file) :
	ranges()
{
	// destination - source - length
	std::regex rangeRegex("(\\d+) (\\d+) (\\d+)");
	std::smatch m;
	std::string line;

	while (!arg_file.eof())
	{
		std::getline(arg_file, line);
		if (line == "")
		{
			break;
		}

		std::regex_search(line, m, rangeRegex);

		uint64_t destination = std::stoull(m[1].str());
		uint64_t source = std::stoull(m[2].str());
		uint64_t length = std::stoull(m[3].str());

		sRange range(source, destination, length);
		ranges.push_back(range);
	}

	std::sort(ranges.begin(), ranges.end(), sRange::Sort);
}

uint64_t cMap::operator[](uint64_t arg_source) const
{
	for (auto& range : ranges)
	{
		if (arg_source < range.sourceStart)
		{
			return arg_source;
		}

		if (range.Contains(arg_source))
		{
			return range.GetDestination(arg_source);
		}
	}

	return arg_source;
}
