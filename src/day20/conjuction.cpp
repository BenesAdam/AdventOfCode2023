#include "conjuction.hpp"

cConjunction::cConjunction(const std::string arg_name, std::list<std::string> arg_neighboursByName) :
	cComponent(arg_name, arg_neighboursByName),
	states()
{
}

void cConjunction::RegisterInputNeighbourExtra(cComponent* arg_component)
{
	if (states.find(arg_component) == states.end())
	{
		states[arg_component] = E_LOW;
	}
}

std::string cConjunction::GetPrefix(void) const
{
	return "&";
}

void cConjunction::ProcessPulse(std::queue<sPulse>& arg_pulses, const sPulse& arg_pulse)
{
	states[arg_pulse.from] = arg_pulse.signal;

	eSignal outputSignal = E_LOW;
	for (auto& inputNeighbour : inputNeighbours)
	{
		if (states[inputNeighbour] != E_HIGH)
		{
			outputSignal = E_HIGH;
			break;
		}
	}

	for (auto& outputNeighbour : outputNeighbours)
	{
		arg_pulses.push(sPulse(outputSignal, this, outputNeighbour));
	}
}
