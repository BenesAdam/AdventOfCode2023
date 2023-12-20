#pragma once

#include <string>
#include <list>
#include <unordered_set>

class cCard
{
public:
	cCard(const std::string& arg_line);

	static std::list<cCard> ParseCards(const std::string& arg_path);
	static uint32_t GetTotalWorth(const std::list<cCard>& arg_cards);

	void Print(void) const;
	uint32_t GetWorth(void) const;

private:
	std::list<uint8_t> ParseNumbers(const std::string& arg_numbers) const;
	bool IsNumberWinning(const uint8_t arg_number) const;

	uint16_t identifier;
	std::unordered_set<uint8_t> winningNumbers;
	std::list<uint8_t> playingNumbers;
};