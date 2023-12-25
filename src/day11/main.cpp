#include <iostream>

#include "image.hpp"

int main(int argc, char* argv[])
{
	//cImage image_part1(SOURCE_DIR"/day11/test1");
	cImage image_part1(SOURCE_DIR"/day11/input");

	const uint64_t expansion = 1000000U;
	//cImage image_part2(SOURCE_DIR"/day11/test1", expansion);
	cImage image_part2(SOURCE_DIR"/day11/input", expansion);

	uint64_t distancePart1 = image_part1.SumOfDistances();
	uint64_t distancePart2 = image_part2.SumOfDistances();

	std::cout << "Sum of distances (expanded by 2): " << distancePart1 << std::endl;
	std::cout << "Sum of distances (expanded by 1M): " << distancePart2 << std::endl;

	return 0;
}
