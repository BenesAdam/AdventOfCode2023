#pragma once

#include <string>
#include <list>
#include <unordered_set>

class cScratchcard
{
public:
	cScratchcard(void);
	cScratchcard(const std::string& arg_line);

	uint32_t GetWorth(void) const;
	uint16_t GetNumberOfMatchedNumbers(void) const;
	uint16_t GetIdentifier(void) const;

private:
	std::list<uint8_t> ParseNumbers(const std::string& arg_numbers) const;
	bool IsNumberWinning(const uint8_t arg_number) const;

	uint16_t identifier;
	std::unordered_set<uint8_t> winningNumbers;
	std::list<uint8_t> playingNumbers;
};