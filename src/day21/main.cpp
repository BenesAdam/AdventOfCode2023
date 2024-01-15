#include <iostream>

#include "map.hpp"

int main(int argc, char* argv[])
{
	//cMap map(SOURCE_DIR"/day21/test1");
	cMap map(SOURCE_DIR"/day21/input");
	
	std::cout << "Garden plots within reach: " << map.GardensWithinReach(64U) << std::endl;

	return 0;
}
