#include <iostream>

#include "almanac.hpp"

int main(int argc, char* argv[])
{
	//cAlmanac almanac(SOURCE_DIR"/day05/test1");
	cAlmanac almanac(SOURCE_DIR"/day05/input");

	std::cout << "Minimal location (part 1): " << almanac.GetMinimalLocation() << std::endl;
	std::cout << "Minimal location (part 2): " << almanac.GetMinimalLocation(true) << std::endl;

	return 0;
}
