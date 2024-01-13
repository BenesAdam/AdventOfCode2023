#include <iostream>

#include "network.hpp"

int main(int argc, char* argv[])
{
	//cNetwork network(SOURCE_DIR"/day20/test2");
	cNetwork network(SOURCE_DIR"/day20/input");

	std::cout << "Part 1: " << network.PushButton(1000) << std::endl;

	return 0;
}
