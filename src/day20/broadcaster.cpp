#include "broadcaster.hpp"

cBroadcaster::cBroadcaster(const std::string arg_name, std::list<std::string> arg_neighboursByName) :
	cComponent(arg_name, arg_neighboursByName)
{
}

std::string cBroadcaster::GetPrefix(void) const
{
	return "";
}

void cBroadcaster::ProcessPulse(std::queue<sPulse>& arg_pulses, const sPulse& arg_pulse)
{
	for (auto& outputNeighbour : outputNeighbours)
	{
		arg_pulses.push(sPulse(arg_pulse.signal, this, outputNeighbour));
	}
}
