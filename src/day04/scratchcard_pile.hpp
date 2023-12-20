#pragma once

#include <string>
#include <unordered_map>
#include <queue>

#include "scratchcard.hpp"

class cScratchcardPile
{
public:
	cScratchcardPile(const std::string& arg_path);

	uint32_t GetTotalWorth(void) const;
	uint32_t GetTotalNumberOfCards(void);

private:
	void ProcessScratchcard(const cScratchcard& arg_card);

	std::unordered_map<uint16_t, cScratchcard> cards;
	std::queue<uint16_t> cardsToProcess;
};