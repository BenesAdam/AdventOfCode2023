#pragma once

#include <string>

#include "position.hpp"

struct sState
{
	enum eDirection : uint8_t
	{
		UP = 0U, RIGHT, DOWN, LEFT
	};

	uint32_t score;
	sPosition<uint16_t> position;
	eDirection direction;
	uint8_t steps;

	sState(const uint32_t arg_score, const sPosition<uint16_t> arg_position, const sState::eDirection arg_direction, const uint8_t arg_steps);
	std::string GetLabelNoScore() const;
	bool operator>(const sState& arg_other) const;
};
