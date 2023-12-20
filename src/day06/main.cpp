#include <iostream>

#include "race.hpp"

int main(int argc, char* argv[])
{
	//auto races_part1 = cRace::Parse(SOURCE_DIR"/day06/test_part1");
	//auto races_part2 = cRace::Parse(SOURCE_DIR"/day06/test_part2");

	auto races_part1 = cRace::Parse(SOURCE_DIR"/day06/input_part1");
	auto races_part2 = cRace::Parse(SOURCE_DIR"/day06/input_part2");

	std::cout << "Part 1: " << cRace::GetPowerOfPossibleStrategies(races_part1) << std::endl;
	std::cout << "Part 2: " << cRace::GetPowerOfPossibleStrategies(races_part2) << std::endl;

	return 0;
}
