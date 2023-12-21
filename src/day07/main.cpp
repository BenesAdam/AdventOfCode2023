#include <iostream>

#include "pocketbet.hpp"

int main(int argc, char* argv[])
{
	//std::vector<cPocketbet> pocketbets = cPocketbet::Parse(SOURCE_DIR"/day07/test1");
	
	cHand::DisableJokers();
	std::vector<cPocketbet> pocketbets_part1 = cPocketbet::Parse(SOURCE_DIR"/day07/input"); 

	cHand::EnableJokers();
	std::vector<cPocketbet> pocketbets_part2 = cPocketbet::Parse(SOURCE_DIR"/day07/input"); 

	std::cout << "Total winnings (part 1): " << cPocketbet::GetTotalWinnings(pocketbets_part1) << std::endl;
	std::cout << "Total winnings (part 2): " << cPocketbet::GetTotalWinnings(pocketbets_part2) << std::endl;

	return 0;
}
