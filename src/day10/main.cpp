#include <iostream>

#include "piping.hpp"

int main(int argc, char* argv[])
{
	//cPiping piping(SOURCE_DIR"/day10/test3");
	cPiping piping(SOURCE_DIR"/day10/input");

	std::cout << piping.StepsToMeetAnimal() << std::endl;
	std::cout << piping.GetNestSize() << std::endl;

	return 0;
}
