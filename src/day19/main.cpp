#include <iostream>

#include "part_sorter.hpp"

int main(int argc, char* argv[])
{
	//cPartSorter partSorter(SOURCE_DIR"/day19/test1");
	cPartSorter partSorter(SOURCE_DIR"/day19/input");

	std::cout << "Sum of accepted parts: " << partSorter.SumOfAccepted() << std::endl;
	std::cout << "Number of combinations: " << partSorter.NumberOfCombinations() << std::endl;

	return 0;
}
