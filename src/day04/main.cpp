#include <iostream>
#include "card.hpp"

int main(int argc, char* argv[])
{
	//std::list<cCard> cards = cCard::ParseCards(SOURCE_DIR"/day04/test1");
	std::list<cCard> cards = cCard::ParseCards(SOURCE_DIR"/day04/input");

  std::cout << "Total point worth: " << cCard::GetTotalWorth(cards) << std::endl;

	return 0;
}
