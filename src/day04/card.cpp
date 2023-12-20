#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <regex>

#include "card.hpp"

std::list<cCard> cCard::ParseCards(const std::string& arg_path)
{
	std::list<cCard> cards;

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
		cCard card(line);
		cards.push_back(card);
	}

	return cards;
}

cCard::cCard(const std::string& arg_line) :
	identifier(0U),
	winningNumbers(),
	playingNumbers()
{
	// Split into groups of identifier, winning numbers, playing numbers
	std::regex regexSplitIntoGroups("Card\\s*(\\d+):((?: *\\d+)+) \\|((?: *\\d+)+)");
	std::smatch m;
	std::regex_search(arg_line, m, regexSplitIntoGroups);

	// Card identifier
	this->identifier = std::stoi(m[1].str());

	// Winning numbers
	std::string strWinningNumbers = m[2].str();
	std::list<uint8_t> listWinningNumbers = ParseNumbers(strWinningNumbers);
	for (auto number : listWinningNumbers)
	{
		this->winningNumbers.insert(number);
	}

	// Playing numbers
	std::string strPlayingNumbers = m[3].str();
	this->playingNumbers = ParseNumbers(strPlayingNumbers);
}

std::list<uint8_t> cCard::ParseNumbers(const std::string& arg_numbers) const
{
	std::list<uint8_t> numbers;

	std::istringstream ss(arg_numbers);
	uint16_t n;
	while (ss >> n)
	{
		numbers.push_back(static_cast<uint8_t>(n));
	}

	return numbers;
}

void cCard::Print(void) const
{
	printf("Card %3d:", identifier);
	for (auto number : winningNumbers)
	{
		printf(" %2d", number);
	}
	printf(" |");
	for (auto number : playingNumbers)
	{
		printf(" %2d", number);
	}
	printf("\n");
}

uint32_t cCard::GetTotalWorth(const std::list<cCard>& arg_cards)
{
	uint32_t totalWorth = 0U;

	for (auto& card : arg_cards)
	{
		totalWorth += card.GetWorth();
	}

	return totalWorth;
}

uint32_t cCard::GetWorth(void) const
{
	uint32_t worth = 0U;

	for (auto playingNumber : playingNumbers)
	{
		if (IsNumberWinning(playingNumber))
		{
			worth = (worth == 0U) ? 1U : (2U * worth);
		}
	}

	return worth;
}

bool cCard::IsNumberWinning(const uint8_t arg_number) const
{
	return winningNumbers.count(arg_number) != 0U;
}
