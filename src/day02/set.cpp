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
	return redCubes <= arg_configuration.redCubes
		&& greenCubes <= arg_configuration.greenCubes
		&& blueCubes <= arg_configuration.blueCubes;
}
