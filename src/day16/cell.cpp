#include "cell.hpp"

const sPosition<int32_t> cCell::Directions[4U] =
{
	/*     UP */ { -1,  0 },
	/*  RIGHT */ {  0,  1 },
	/* BOTTOM */ {  1,  0 },
	/*   LEFT */ {  0, -1 },
};

const std::vector<std::map<char, std::vector<cCell::eDirection>>> cCell::router
{
	/* UP */
	{
		{'.',  {eDirection::UP}},
		{'|',  {eDirection::UP}},
		{'-',  {eDirection::LEFT, eDirection::RIGHT}},
		{'\\', {eDirection::LEFT}},
		{'/',  {eDirection::RIGHT}},
	},
	/* RIGHT */
	{
		{'.',  {eDirection::RIGHT}},
		{'-',  {eDirection::RIGHT}},
		{'|',  {eDirection::UP, eDirection::BOTTOM}},
		{'\\', {eDirection::BOTTOM}},
		{'/',  {eDirection::UP}},
	},
	/* BOTTOM */
	{
		{'.',  {eDirection::BOTTOM}},
		{'|',	 {eDirection::BOTTOM}},
		{'-',	 {eDirection::LEFT, eDirection::RIGHT}},
		{'\\', {eDirection::RIGHT}},
		{'/',	 {eDirection::LEFT}},
	},
	/* LEFT */
	{
		{'.',  {eDirection::LEFT}},
		{'-',  {eDirection::LEFT}},
		{'|',  {eDirection::UP, eDirection::BOTTOM}},
		{'\\', {eDirection::UP}},
		{'/',  {eDirection::BOTTOM}},
	},
};

std::string cCell::sBeam::GetLabel(void) const
{
	return std::to_string(static_cast<uint8_t>(direction)) + "-" + std::to_string(position.i) + "-" + std::to_string(position.j);
}

cCell::cCell(void) :
	symbol('.'),
	voltageLevel(0U)
{
}

cCell::cCell(const char c) :
	symbol(c),
	voltageLevel(0U)
{
}

char cCell::GetSymbol(void) const
{
	return symbol;
}

bool cCell::IsEnergized(void) const
{
	return voltageLevel > 0U;
}

void cCell::ResetVoltageLevel(void)
{
	voltageLevel = 0U;
}

uint16_t cCell::ProccessBeam(const sPosition<int32_t>& arg_dimensions, const cCell::sBeam& arg_beam, std::stack<cCell::sBeam>& arg_beams)
{
	voltageLevel++;

	const std::vector<eDirection>& directions = router[static_cast<uint8_t>(arg_beam.direction)].at(symbol);
	for (auto& direction : directions)
	{
		sPosition<int32_t> position = arg_beam.position + Directions[static_cast<uint8_t>(direction)];
		if (position.IsInBoundary(arg_dimensions.i, arg_dimensions.j))
		{
			sBeam beam = { direction, position };
			arg_beams.push(beam);
		}
	}

	return (voltageLevel == 1U) ? 1U : 0U;
}
