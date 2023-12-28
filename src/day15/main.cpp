#include <iostream>

#include "init_sequence.hpp"

int main(int argc, char* argv[])
{
	// cInitSequence initSequence(SOURCE_DIR"/day15/test1");
	cInitSequence initSequence(SOURCE_DIR"/day15/input");

	std::cout << initSequence.HashSum() << std::endl;

	return 0;
}
