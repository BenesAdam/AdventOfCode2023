#include "dummy_component.hpp"

cDummyComponent::cDummyComponent(const std::string& arg_name) :
	cComponent(arg_name)
{
}

void cDummyComponent::ProcessPulse(std::queue<sPulse>& arg_pulses, const sPulse& arg_pulse)
{
}

std::string cDummyComponent::GetPrefix(void) const
{
	return "*";
}
