#include <iostream>

#include "report.hpp"

int main(int argc, char* argv[])
{
	//std::list<cReport> reports = cReport::Parse(SOURCE_DIR"/day09/test1");
	std::list<cReport> reports = cReport::Parse(SOURCE_DIR"/day09/input");

	std::cout << "Sum of extrapolated values: " << cReport::SumOfExtrapolatedValues(reports) << std::endl;

	return 0;
}
