#include <iostream>

#include "map.hpp"

int main(int argc, char* argv[])
{
	//cMap map(SOURCE_DIR"/day08/test3");
	cMap map(SOURCE_DIR"/day08/input");

	std::cout << "Human steps to reach finish: " << map.GetSteps() << std::endl;
	std::cout << "Ghost steps to reach finish: " << map.GetGhostSteps() << std::endl;

	return 0;
}
