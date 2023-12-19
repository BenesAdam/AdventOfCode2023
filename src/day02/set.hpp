#pragma once

#include <string>

struct cSet
{
	cSet(void);
	cSet(const uint16_t arg_red, const uint16_t arg_green, const uint16_t arg_blue);
	cSet(std::string& arg_stringSet);

	bool IsPossible(const cSet& arg_configuration) const;

	enum eColor
	{
		RED = 0U,
		GREEN,
		BLUE,
	};

	uint16_t redCubes;
	uint16_t greenCubes;
	uint16_t blueCubes;
};
