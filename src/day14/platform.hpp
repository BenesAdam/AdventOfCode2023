#pragma once

#include <string>
#include <vector>

class cPlatform
{
public:
	cPlatform(const std::string& arg_path);

	void Print(void) const;
	uint32_t TotalNorthLoad(void);

private:
	void TiltNorth(void);
	void TiltNorth(const uint16_t arg_i, const uint16_t arg_j);

	uint16_t NumberOfRoundedRocks(const uint16_t arg_i) const;

	uint16_t width;
	uint16_t height;
	std::vector<std::string> data;
};
