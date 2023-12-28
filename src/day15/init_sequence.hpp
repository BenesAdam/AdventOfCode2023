#pragma once

#include <string>
#include <list>

class cInitSequence
{
public:
	cInitSequence(const std::string& arg_path);

	static uint8_t Hash(const std::string& arg_string);

	uint32_t HashSum(void) const;

private:
	std::list<std::string> objects;
};
