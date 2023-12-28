#pragma once

#include <string>
#include <list>
#include <unordered_set>

struct sLens
{
	enum class eOperation {ADD, REMOVE};
	
	std::string label;
	eOperation operation;
	uint16_t focalLength;

	sLens(void);
	sLens(const std::string& arg_input);
};

class cBox
{
public:
	cBox();

	bool Empty(void) const;
	void Add(const sLens& arg_lens);
	void Remove(const sLens& arg_lens);

	uint32_t FocusingPower(const uint16_t arg_BoxNumber) const;

private:
	std::unordered_set<std::string> labels;
	std::list<sLens> lenses;
};
