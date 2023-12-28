#pragma once

#include <string>
#include <list>
#include <array>

#include "box.hpp"

class cInitSequence
{
public:
	cInitSequence(const std::string& arg_path);

	static uint8_t Hash(const std::string& arg_string);

	uint32_t ObjectsHashSum(void) const;
	uint32_t FocusingPower(void) const;

private:
	void ProcessObject(const std::string& arg_object);

	static const uint16_t boxCount = 256U;

	std::list<std::string> objects;
	uint32_t objectsHashSum;
	std::array<cBox, boxCount> boxes;
};
