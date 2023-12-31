#include "state.hpp"

sState::sState(const uint32_t arg_score, const sPosition<uint16_t> arg_position,
	const sState::eDirection arg_direction, const uint8_t arg_steps) :
	score(arg_score),
	position(arg_position),
	direction(arg_direction),
	steps(arg_steps)
{
}

std::string sState::GetLabelNoScore() const
{
	return std::to_string(position.i) + "-" + std::to_string(position.j) + "-" + std::to_string(direction) + "-" + std::to_string(steps);
}

bool sState::operator>(const sState& arg_other) const
{
	return this->score > arg_other.score;
}
