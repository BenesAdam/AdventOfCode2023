#pragma once

#include <string>
#include <map>

#include "component.hpp"

class cNetwork
{
public:
	cNetwork(const std::string arg_path);

	void Print(void) const;
	uint32_t PushButton(const uint32_t arg_count = 1U);
	void Reset(void);
	uint64_t RequiredButtonPushes(void);

private:
	std::set<cComponent*> GetLastConjuctions(void);
	std::list<uint32_t> GetCycleLengths(std::set<cComponent*>& arg_lastComponents);

	std::map<std::string, cComponent*> components;
	cComponent* broadcaster;
};
