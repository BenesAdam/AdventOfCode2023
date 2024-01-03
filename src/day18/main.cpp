#include <iostream>

#include "instruction.hpp"

int main(int argc, char* argv[])
{
	std::list<cInstraction> part1;
	std::list<cInstraction> part2;

	// cInstraction::ParseFile(SOURCE_DIR"/day18/test1", part1, part2);
	cInstraction::ParseFile(SOURCE_DIR"/day18/input", part1, part2);

	std::cout << "Part 1: " << cInstraction::ComputeCubicMetersOfLava(part1) << std::endl;
	std::cout << "Part 2: " << cInstraction::ComputeCubicMetersOfLava(part2) << std::endl;

	return 0;
}
