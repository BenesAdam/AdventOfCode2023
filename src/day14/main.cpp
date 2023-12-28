#include <iostream>

#include "platform.hpp"

int main(int argc, char* argv[])
{
	// cPlatform platform_part1(SOURCE_DIR"/day14/test1");
	cPlatform platform_part1(SOURCE_DIR"/day14/input");

	std::cout << "Total load (part 1): " << platform_part1.TotalNorthLoadPart1() << std::endl;

	//cPlatform platform_part2(SOURCE_DIR"/day14/test1");
	cPlatform platform_part2(SOURCE_DIR"/day14/input");

	std::cout << "Total load (part 2): " << platform_part2.TotalNorthLoadPart2(1000000000U) << std::endl;

	return 0;
}
