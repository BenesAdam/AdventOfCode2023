#include <iostream>

#include "condition_record.hpp"

int main(int argc, char* argv[])
{
	cConditionRecord::GlobalEnableFolding(false);
	//std::list<cConditionRecord> records_part1 = cConditionRecord::ParseFile(SOURCE_DIR"/day12/test1");
	std::list<cConditionRecord> records_part1 = cConditionRecord::ParseFile(SOURCE_DIR"/day12/input");
	std::cout << "Number of different arrangements (brute force): " << cConditionRecord::NumberOfPossibleWayBruteForce(records_part1) << std::endl;

	//cConditionRecord::GlobalEnableFolding(true);
	////std::list<cConditionRecord> records_part2 = cConditionRecord::ParseFile(SOURCE_DIR"/day12/test1");
	//std::list<cConditionRecord> records_part2 = cConditionRecord::ParseFile(SOURCE_DIR"/day12/input");
	//std::cout << "Number of different arrangements (part 2): " << cConditionRecord::NumberOfPossibleWayBruteForce(records_part2) << std::endl;

	return 0;
}
