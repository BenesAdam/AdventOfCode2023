#pragma once

#include "component.hpp"

class cDummyComponent : public cComponent
{
public:
	cDummyComponent(const std::string& arg_name);

private:
	void ProcessPulse(std::queue<sPulse>& arg_pulses, const sPulse& arg_pulse) override;
	std::string GetPrefix(void) const override;
};
