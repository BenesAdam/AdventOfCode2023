#include <iostream>

#include "part_sorter.hpp"

int main(int argc, char* argv[])
{
	//cPartSorter partSorter(SOURCE_DIR"/day19/test1");
	cPartSorter partSorter(SOURCE_DIR"/day19/input");
	uint64_t acceptedParts = partSorter.SumOfAccepted();
	std::cout << "Sum of accepted parts: " << acceptedParts << std::endl;

	if (acceptedParts == 421983)
	{
		std::cout << "GOOD" << std::endl;
	}
	else
	{
		std::cout << "FAIL" << std::endl;
	}

	return 0;
}
