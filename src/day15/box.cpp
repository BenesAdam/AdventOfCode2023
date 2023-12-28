#include <sstream>
#include <iostream>

#include "box.hpp"

sLens::sLens(void) :
	label(),
	operation(sLens::eOperation::ADD),
	focalLength(UINT16_MAX)
{
}

sLens::sLens(const std::string& arg_input) :
	sLens()
{
	std::stringstream strStream(arg_input);

	char c;
	while (strStream.good())
	{
		strStream >> c;

		if (c == '=')
		{
			operation = eOperation::ADD;
			break;
		}
		else if (c == '-')
		{
			operation = eOperation::REMOVE;
			break;
		}
		else
		{
			label += c;
		}
	}

	if (strStream.good())
	{
		strStream >> focalLength;
	}
}

cBox::cBox() :
	labels(),
	lenses()
{
}

void cBox::Add(const sLens& arg_lens)
{
	if (labels.find(arg_lens.label) != labels.end())
	{
		for (auto& lens : lenses)
		{
			if (lens.label == arg_lens.label)
			{
				lens.focalLength = arg_lens.focalLength;
				break;
			}
		}
	}
	else
	{
		labels.insert(arg_lens.label);
		lenses.push_back(arg_lens);
	}
}

void cBox::Remove(const sLens& arg_lens)
{
	if (labels.find(arg_lens.label) != labels.end())
	{
		labels.erase(arg_lens.label);

		for (auto it = lenses.begin(); it != lenses.end(); ++it)
		{
			if ((*it).label == arg_lens.label)
			{
				lenses.erase(it);
				break;
			}
		}
	}
}

uint32_t cBox::FocusingPower(const uint16_t arg_BoxNumber) const
{
	uint32_t sum = 0U; 

	uint32_t slotNumber = 1U;
	for (auto& lens : lenses)
	{
		sum += arg_BoxNumber * slotNumber * lens.focalLength;
		slotNumber++;
	}

	return sum;
}

bool cBox::Empty(void) const
{
	return lenses.empty();
}
