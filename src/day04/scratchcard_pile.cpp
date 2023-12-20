#include <iostream>
#include <fstream>

#include "scratchcard_pile.hpp"

cScratchcardPile::cScratchcardPile(const std::string& arg_path) :
	cards(),
	cardsToProcess()
{
	std::ifstream file(arg_path);

	if (!file.is_open())
	{
		std::cout << "File is not found." << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string line;
	while (!file.eof())
	{
		std::getline(file, line);
		cScratchcard card(line);

		const uint16_t identifier = card.GetIdentifier();
		cards.emplace(identifier, card);
		cardsToProcess.push(identifier);
	}
}

uint32_t cScratchcardPile::GetTotalWorth(void) const
{
	uint32_t totalWorth = 0U;

	for (auto& card : cards)
	{
		totalWorth += card.second.GetWorth();
	}

	return totalWorth;
}

uint32_t cScratchcardPile::GetTotalNumberOfCards(void)
{
	uint32_t numberOfCards = 0U;

	while(!cardsToProcess.empty())
	{
		const uint16_t identifier = cardsToProcess.front();
		cardsToProcess.pop();

		numberOfCards++;
		ProcessScratchcard(cards[identifier]);
	}

	return numberOfCards;
}

void cScratchcardPile::ProcessScratchcard(const cScratchcard& arg_card)
{
	uint16_t numberOfMatched = arg_card.GetNumberOfMatchedNumbers();

	if (numberOfMatched > 0U)
	{
		const uint16_t identifier = arg_card.GetIdentifier();
		for (uint16_t i = 1U; i <= numberOfMatched; i++)
		{
			cardsToProcess.push(identifier + i);
		}
	}
}
