#include <iostream>

#include "contraption.hpp"

int main(int argc, char* argv[])
{
	// cContraption contraption(SOURCE_DIR"/day16/test1");
	cContraption contraption(SOURCE_DIR"/day16/input");

	std::cout << contraption.CountEnergizedTiles() << std::endl;

	return 0;
}
