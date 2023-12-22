#include <iostream>

#include "report.hpp"

int main(int argc, char* argv[])
{
	//std::list<cReport> reports = cReport::Parse(SOURCE_DIR"/day09/test2");
	std::list<cReport> reports = cReport::Parse(SOURCE_DIR"/day09/input");

	std::cout << "Sum of forwards extrapolated values: " << cReport::SumOfExtrapolatedValues(reports, false) << std::endl;
	std::cout << "Sum of backwards extrapolated values: " << cReport::SumOfExtrapolatedValues(reports, true) << std::endl;

	return 0;
}
