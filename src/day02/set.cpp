#include "set.hpp"
#include <regex>

cSet::cSet(void) :
	redCubes(0U),
	greenCubes(0U),
	blueCubes(0U)
{
}

cSet::cSet(const uint16_t arg_red, const uint16_t arg_green, const uint16_t arg_blue) :
	redCubes(arg_red),
	greenCubes(arg_green),
	blueCubes(arg_blue)
{
}

cSet::cSet(std::string& arg_stringSet) :
	cSet()
{
	std::string digitSubstring = "";

	for (char c : arg_stringSet)
	{
		if (isdigit(c))
		{
			digitSubstring += c;
			continue;
		}

		uint16_t count = std::stoi(digitSubstring);
		digitSubstring = "";

		switch (c)
		{
		case 'R':
			redCubes = count;
			break;
		case 'G':
			greenCubes = count;
			break;
		case 'B':
			blueCubes = count;
			break;
		default:
			break;
		}
	}
}

bool cSet::IsPossible(const cSet& arg_configuration) const
{
	return
		redCubes <= arg_configuration.redCubes &&
		greenCubes <= arg_configuration.greenCubes &&
		blueCubes <= arg_configuration.blueCubes;
}

void cSet::Max(cSet& arg_maximum) const
{
	arg_maximum.redCubes = std::max(arg_maximum.redCubes, this->redCubes);
	arg_maximum.greenCubes = std::max(arg_maximum.greenCubes, this->greenCubes);
	arg_maximum.blueCubes = std::max(arg_maximum.blueCubes, this->blueCubes);
}

uint32_t cSet::Mul(void) const
{
	return
		static_cast<uint32_t>(redCubes) *
		static_cast<uint32_t>(greenCubes) *
		static_cast<uint32_t>(blueCubes);
}
