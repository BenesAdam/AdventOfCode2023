#pragma once

#include <position.hpp>
#include <stack>
#include <map>
#include <vector>
#include <string>
#include <set>

class cCell
{
public:
	enum class eDirection
	{
		UP, RIGHT, BOTTOM, LEFT
	};

	struct sBeam
	{
		cCell::eDirection direction;
		sPosition<int32_t> position;

		std::string GetLabel(void) const;
	};

	cCell(void);
	cCell(const char c);

	char GetSymbol(void) const;
	bool IsEnergized(void) const;
	void ResetVoltageLevel(void);
	uint16_t ProccessBeam(const sPosition<int32_t>& arg_dimensions, const cCell::sBeam& arg_beam, std::stack<cCell::sBeam>& arg_beams);
	
	static const sPosition<int32_t> Directions[4U];

private:
	static const std::vector<std::map<char, std::vector<cCell::eDirection>>> router;
	static std::set<std::string> visit;

	char symbol;
	uint16_t voltageLevel;
};
