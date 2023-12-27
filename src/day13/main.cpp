#include <iostream>

#include "pattern.hpp"

int main(int argc, char* argv[])
{
	// std::list<cPattern> patterns = cPattern::ParseFile(SOURCE_DIR"/day13/test3");
	std::list<cPattern> patterns = cPattern::ParseFile(SOURCE_DIR"/day13/input");

	uint32_t reflectionSummarization = cPattern::ReflectionSummarization(patterns);
	std::cout << "Reflection summarization: " << reflectionSummarization << std::endl;

	return 0;
}
