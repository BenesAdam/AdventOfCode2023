#include <iostream>

#include "platform.hpp"

int main(int argc, char* argv[])
{
	// cPlatform platform(SOURCE_DIR"/day14/test1");
	cPlatform platform(SOURCE_DIR"/day14/input");

	std::cout << "Total load on the north support beams: " << platform.TotalNorthLoad() << std::endl;

	return 0;
}
