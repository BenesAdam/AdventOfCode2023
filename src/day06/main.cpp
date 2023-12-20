#include <iostream>

#include "race.hpp"

int main(int argc, char* argv[])
{
	//auto races = cRace::Parse(SOURCE_DIR"/day06/test1");
	auto races = cRace::Parse(SOURCE_DIR"/day06/input");

	std::cout << cRace::GetPowerOfPossibleStrategies(races) << std::endl;

	return 0;
}
