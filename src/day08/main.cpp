#include <iostream>

#include "map.hpp"

int main(int argc, char* argv[])
{
	//cMap map(SOURCE_DIR"/day08/test2");
	cMap map(SOURCE_DIR"/day08/input");

	std::cout << "Steps to reach ZZZ: " << map.GetSteps() << std::endl;

	return 0;
}
