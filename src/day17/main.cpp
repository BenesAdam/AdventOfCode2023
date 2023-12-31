#include <iostream>

#include "map.hpp"

int main(int argc, char* argv[])
{
	// cMap map(SOURCE_DIR"/day17/test1");
	cMap map(SOURCE_DIR"/day17/input");

	std::cout << "Part 1: " << map.GetLeastHeatLoss(0U, 3U) << std::endl;
	std::cout << "Part 2: " << map.GetLeastHeatLoss(4U, 10U) << std::endl;

	return 0;
}
