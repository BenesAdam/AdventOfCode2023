#include <iostream>

#include "map.hpp"

int main(int argc, char* argv[])
{
	cMap map(SOURCE_DIR"/day21/input");
	
	map.Compute(64U);

	return 0;
}
