#include <regex>

#include "part.hpp"

sPart::sPart(const std::string& arg_line) :
	rating()
{
	std::smatch m;
	std::regex regex("\\{x=(\\d+),m=(\\d+),a=(\\d+),s=(\\d+)\\}");
	std::regex_search(arg_line, m, regex);

	rating[ExtremelyCoolLooking] = std::stoi(m[1]);
	rating[Musical] = std::stoi(m[2]);
	rating[Aerodynamic] = std::stoi(m[3]);
	rating[Shiny] = std::stoi(m[4]);
}

sPart::sPart(const uint16_t arg_value) :
	rating()
{
	for (uint8_t i = 0U; i < CategorySize; i++)
	{
		rating[i] = arg_value;
	}
}

sPart::eCategory sPart::LetterToCategory(const char arg_c)
{
	switch (arg_c)
	{
	case 'x':
		return sPart::ExtremelyCoolLooking;
	case 'm':
		return sPart::Musical;
	case 'a':
		return sPart::Aerodynamic;
	case 's':
	default:
		return sPart::Shiny;
		break;
	}
}

uint64_t sPart::GetFinalRating(void) const
{
	uint64_t result = 0U;

	for (uint8_t i = 0U; i < sPart::CategorySize; i++)
	{
		result += rating[i];
	}

	return result;
}

sInterval::sInterval(void) :
	min(1U),
	max(4000U)
{
}

sInterval::sInterval(const uint16_t arg_minValue, const uint16_t arg_maxValue) :
	min(arg_minValue),
	max(arg_maxValue)
{
}
