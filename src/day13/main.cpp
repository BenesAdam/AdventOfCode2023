#include <iostream>

#include "pattern.hpp"

int main(int argc, char* argv[])
{
	// std::list<cPattern> patterns = cPattern::ParseFile(SOURCE_DIR"/day13/test1");
	std::list<cPattern> patterns = cPattern::ParseFile(SOURCE_DIR"/day13/input");

	std::cout << "Reflection summarization: " << cPattern::ReflectionSummarization(patterns) << std::endl;

	// std::cout << "   Horizontal reflection: " << patterns.front().FindHorizontalReflection() << std::endl;
	// std::cout << "     Vertical reflection: " << patterns.front().FindVerticalReflection() << std::endl;
	// std::cout << "Reflection summarization: " << patterns.front().ReflectionSummarization() << std::endl;

	return 0;
}
