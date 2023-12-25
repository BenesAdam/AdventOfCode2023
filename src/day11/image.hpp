#pragma once

#include <string>
#include <vector>

#include "position.hpp"

class cImage
{
public:
	cImage(void);
	cImage(const cImage* const arg_image);
	cImage(const std::string& arg_path);

	static cImage GetExpanded(const cImage& arg_image);

	uint32_t SumOfDistances(void);
	uint32_t SumOfExpandedDistances(void);

	void Print(void) const;
	void PrintPositions(void) const;

private:
	void ParseFile(const std::string& arg_path);
	void RecalculatePositions(void);

	void Expand(void);
	void ExpandVertical(void);
	void ExpandHorizontal(void);

	uint16_t width;
	uint16_t height;
	std::vector<std::string> data;
	std::vector<sPosition<uint16_t>> positions;
};
