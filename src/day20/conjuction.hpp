#pragma once

#include "component.hpp"

class cConjunction : public cComponent
{
public:
  cConjunction(const std::string arg_name, std::list<std::string> arg_neighboursByName);

private:
  std::string GetPrefix(void) const override;
  void ProcessPulse(std::queue<sPulse>& arg_pulses, const sPulse& arg_pulse) override;
  void RegisterInputNeighbourExtra(cComponent* arg_component) override;

  std::map<cComponent*, eSignal> states;
};
