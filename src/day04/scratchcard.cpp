#include <iostream>
#include <cstdio>
#include <sstream>
#include <regex>

#include "scratchcard.hpp"

cScratchcard::cScratchcard(void) :
	identifier(0U),
	winningNumbers(),
	playingNumbers()
{
}

cScratchcard::cScratchcard(const std::string& arg_line) :
	cScratchcard()
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

std::list<uint8_t> cScratchcard::ParseNumbers(const std::string& arg_numbers) const
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

uint32_t cScratchcard::GetWorth(void) const
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

bool cScratchcard::IsNumberWinning(const uint8_t arg_number) const
{
	return winningNumbers.count(arg_number) != 0U;
}

uint16_t cScratchcard::GetNumberOfMatchedNumbers(void) const
{
	uint16_t numberOfCards = 0U;

	for (auto playingNumber : playingNumbers)
	{
		numberOfCards = (IsNumberWinning(playingNumber)) ? (numberOfCards + 1U) : numberOfCards;
	}

	return numberOfCards;
}

uint16_t cScratchcard::GetIdentifier(void) const
{
	return identifier;
}
