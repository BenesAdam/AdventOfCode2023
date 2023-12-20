#include <iostream>
#include "scratchcard_pile.hpp"

int main(int argc, char* argv[])
{
	//cScratchcardPile pile(SOURCE_DIR"/day04/test1");
	cScratchcardPile pile(SOURCE_DIR"/day04/input");

  std::cout << "Total point worth: " << pile.GetTotalWorth() << std::endl;
  std::cout << "Number of cards in pile: " << pile.GetTotalNumberOfCards() << std::endl;

	return 0;
}
