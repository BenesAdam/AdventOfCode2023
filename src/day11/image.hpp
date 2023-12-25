#pragma once

#include <string>
#include <vector>

#include "position.hpp"

class cImage
{
public:
	cImage(void);
	cImage(const std::string& arg_path, const uint64_t arg_expansion = 2U);

	uint64_t SumOfDistances(void);

private:
	void ParseFile(const std::string& arg_path);
	void CalculatePositions(void);

	void ExpandPositions(void);
	void ExpandVertical(void);
	void ExpandHorizontal(void);

	uint16_t width;
	uint16_t height;
	std::vector<std::string> data;
	std::vector<sPosition<uint64_t>> positions;
	uint64_t expansion;
};
