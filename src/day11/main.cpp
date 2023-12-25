#include <iostream>

#include "image.hpp"

int main(int argc, char* argv[])
{
	//cImage image(SOURCE_DIR"/day11/test1");
	cImage image(SOURCE_DIR"/day11/input");

	std::cout << "Sum of distances: " << image.SumOfExpandedDistances() << std::endl;

	return 0;
}
