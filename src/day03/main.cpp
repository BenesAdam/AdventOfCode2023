#include <iostream>

#include "engine_schematic.hpp"

int main(int argc, char* argv[])
{
	// https://adventofcode.com/2023/day/3

	//cEngineSchematic schematic(SOURCE_DIR"/day03/test1");
	cEngineSchematic schematic(SOURCE_DIR"/day03/input");

	std::cout << "Sum of parts is: " << schematic.GetSumOfParts() << std::endl;
	std::cout << "Sum of gear ratio is: " << schematic.GetSumOfGearRatio() << std::endl;

	return 0;
}
