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

private:
	std::map<std::string, cComponent*> components;
	cComponent* broadcaster;
};
