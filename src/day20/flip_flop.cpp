#include "flip_flop.hpp"

cFlipFlop::cFlipFlop(const std::string arg_name, std::list<std::string> arg_neighboursByName) :
	cComponent(arg_name, arg_neighboursByName),
	state(E_LOW)
{
}

std::string cFlipFlop::GetPrefix(void) const
{
	return "%";
}

void cFlipFlop::ProcessPulse(std::queue<sPulse>& arg_pulses, const sPulse& arg_pulse)
{
	if (arg_pulse.signal == E_HIGH)
	{
		return;
	}

	state = (state == E_LOW) ? E_HIGH : E_LOW;

	for (auto& outputNeighbour : outputNeighbours)
	{
		arg_pulses.push(sPulse(state, this, outputNeighbour));
	}
}
