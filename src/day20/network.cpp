#include "network.hpp"

cNetwork::cNetwork(const std::string arg_path) :
	components(),
	broadcaster(nullptr)
{
	components = cComponent::ParseFile(arg_path);
	broadcaster = components["broadcaster"];

	for (auto& component : components)
	{
		component.second->Init(components);
	}
}

void cNetwork::Print(void) const
{
	for (auto& component : components)
	{
		component.second->Print();
	}
}

uint32_t cNetwork::PushButton(const uint32_t arg_count)
{
	uint32_t lowPulses = 0U;
	uint32_t highPulses = 0U;

	std::queue<cComponent::sPulse> pulses;

	for (uint32_t i = 0U; i < arg_count; i++)
	{
		pulses.push(cComponent::sPulse(cComponent::E_LOW, nullptr, broadcaster));

		while (!pulses.empty())
		{
			cComponent::sPulse pulse = pulses.front();
			pulses.pop();

			if (pulse.signal == cComponent::E_LOW)
			{
				lowPulses++;
			}
			else
			{
				highPulses++;
			}

			pulse.to->ProcessPulse(pulses, pulse);
		}
	}

	return lowPulses * highPulses;
}
