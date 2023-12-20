#include <iostream>

#include "pocketbet.hpp"

int main(int argc, char* argv[])
{
	//std::vector<cPocketbet> pocketbets = cPocketbet::Parse(SOURCE_DIR"/day07/test1");
	std::vector<cPocketbet> pocketbets = cPocketbet::Parse(SOURCE_DIR"/day07/input");

	std::cout << "Total winnings: " << cPocketbet::GetTotalWinnings(pocketbets) << std::endl;

	return 0;
}
