#pragma once

#include "component.hpp"

class cBroadcaster : public cComponent
{
public:
  cBroadcaster(const std::string arg_name, std::list<std::string> arg_neighboursByName);

private:
  std::string GetPrefix(void) const override;
  void ProcessPulse(std::queue<sPulse>& arg_pulses, const sPulse& arg_pulse) override;
};
