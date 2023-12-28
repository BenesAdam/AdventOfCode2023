#pragma once

#include <string>
#include <vector>
#include <set>

#include "cell.hpp"

class cContraption
{
public:
	cContraption(const std::string& arg_path);

	uint16_t EnergizedTilesUncontrolled(void) const;
	uint16_t EnergizedTilesControlled(void) const;

private:
	void FireBeams(void);
	uint16_t FireBeam(const cCell::sBeam arg_beam);
	void ResetVisitings(void);

	static std::set<std::string> visit;

	uint16_t width;
	uint16_t height;
	std::vector<std::vector<cCell>> data;

	uint16_t energizedTilesUncontrolled;
	uint16_t energizedTilesControlled;
};
