#pragma once

#include <string>

struct sPart
{
	enum eCategory
	{
		ExtremelyCoolLooking,
		Musical,
		Aerodynamic,
		Shiny
	};

	static const uint8_t CategorySize = 4U;
	uint16_t rating[CategorySize];

	sPart(const std::string& arg_line);
	sPart(const uint16_t arg_value);

	static eCategory LetterToCategory(const char arg_c);
	uint64_t GetFinalRating(void) const;
};

struct sInterval
{
	sPart min;
	sPart max;

	sInterval(void);
	sInterval(const uint16_t arg_minValue, const uint16_t arg_maxValue);

	uint64_t CalculateProduct(void) const;
};
