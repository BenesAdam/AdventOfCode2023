#pragma once

#include <string>
#include <vector>

class cMap
{
public:
	cMap(const std::string& arg_path);

	uint32_t GetLeastHeatLoss(const uint8_t arg_minSteps, const uint8_t arg_maxSteps);

private:
	uint16_t width;
	uint16_t height;
	std::vector<std::string> data;
};
