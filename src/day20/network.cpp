#include <iostream>

#include "network.hpp"
#include "numeric.hpp"

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

void cNetwork::Reset(void)
{
	for (auto& component : components)
	{
		component.second->Reset();
	}
}

uint64_t cNetwork::RequiredButtonPushes(void)
{
	std::set<cComponent*> lastComponents = GetLastConjuctions();
	std::list<uint32_t> cycleLengths = GetCycleLengths(lastComponents);

	uint64_t pushes = 1U;
	for (auto& cycleLength : cycleLengths)
	{
		pushes = nsNumeric::LeastCommonMultiple(pushes, static_cast<uint64_t>(cycleLength));
	}

	return pushes;
}

std::set<cComponent*> cNetwork::GetLastConjuctions(void)
{
	cComponent* finalComponent = components["rx"];
	cComponent* inputOfFinalComponent = *finalComponent->GetInputNeighbours().begin();
	return inputOfFinalComponent->GetInputNeighbours();
}

std::list<uint32_t> cNetwork::GetCycleLengths(std::set<cComponent*>& arg_lastComponents)
{
	std::map<cComponent*, uint32_t> cyclesPerComponent;
	uint32_t pushes = 0U;

	while (true)
	{
		// Next push of a button
		pushes++;
		std::queue<cComponent::sPulse> pulses;
		pulses.push(cComponent::sPulse(cComponent::E_LOW, nullptr, broadcaster));

		while (!pulses.empty())
		{
			// For every pulse
			cComponent::sPulse pulse = pulses.front();
			pulses.pop();

			// If pulse high pulse feeds into that module that is feeding into rx module
			if ((pulse.signal == cComponent::E_HIGH) && (arg_lastComponents.find(pulse.from) != arg_lastComponents.end()))
			{
				// Count number of pushes if not counted yet
				const bool alreadyCounted = cyclesPerComponent.find(pulse.from) != cyclesPerComponent.end();
				if (!alreadyCounted)
				{
					cyclesPerComponent[pulse.from] = pushes;
				}
			}

			// When all conjuctions are counted return cycle lengths
			if (cyclesPerComponent.size() == arg_lastComponents.size())
			{
				std::list<uint32_t> result;
				for (auto& component : cyclesPerComponent)
				{
					result.push_back(component.second);
				}
				return result;
			}

			// Process pulse
			pulse.to->ProcessPulse(pulses, pulse);
		}
	}
}
