#include <iostream>

#include "init_sequence.hpp"

int main(int argc, char* argv[])
{
	// cInitSequence initSequence(SOURCE_DIR"/day15/test1");
	cInitSequence initSequence(SOURCE_DIR"/day15/input");

	std::cout << "Objects hash sum: " << initSequence.ObjectsHashSum() << std::endl;
	std::cout << "Focusing power: " << initSequence.FocusingPower() << std::endl;

	return 0;
}
