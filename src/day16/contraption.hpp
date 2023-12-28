#pragma once

#include <string>
#include <vector>
#include <set>

#include "cell.hpp"

class cContraption
{
public:
	cContraption(const std::string& arg_path);

	uint16_t CountEnergizedTiles(void) const;

	void Print(void) const;
	void Print(const sPosition<int32_t>& arg_position) const;

private:
	void SpreadBeams(void);

	static std::set<std::string> visit;

	uint16_t width;
	uint16_t height;
	std::vector<std::vector<cCell>> data;
};
