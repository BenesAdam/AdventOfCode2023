#include <iostream>

#include "almanac.hpp"

int main(int argc, char* argv[])
{
	//cAlmanac almanac(SOURCE_DIR"/day05/test1");
	cAlmanac almanac(SOURCE_DIR"/day05/input");

	std::cout << "Minimal location: " << almanac.GetMinimalLocation() << std::endl;

	return 0;
}
