#include <iostream>

#include "network.hpp"

int main(int argc, char* argv[])
{
	//cNetwork network(SOURCE_DIR"/day20/test3");
	cNetwork network(SOURCE_DIR"/day20/input");

	std::cout << "Part 1: " << network.PushButton(1000U) << std::endl;

	network.Reset();
	std::cout << "Part 2: " << network.RequiredButtonPushes() << std::endl;

	return 0;
}
