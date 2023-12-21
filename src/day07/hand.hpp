#pragma once

#include <string>
#include <array>

class cHand
{
public:
	enum class eType
	{
		HIGH_CARD = 0,
		ONE_PAIR,
		TWO_PAIR,
		THREE_OF_A_KIND,
		FULL_HOUSE,
		FOUR_OF_A_KIND,
		FIVE_OF_A_KIND,
	};

	cHand(void);
	cHand(const std::string& arg_cards);

	int8_t Compare(const cHand& other) const;

	static void EnableJokers(void);
	static void DisableJokers(void);

	static const uint8_t NumberOfCards = 5U;

	// operators
	bool operator==(const cHand& other) const;
	bool operator!=(const cHand& other) const;
	bool operator<(const cHand& other) const;
	bool operator<=(const cHand& other) const;
	bool operator>(const cHand& other) const;
	bool operator>=(const cHand& other) const;

private:
	uint8_t ConvertSymbolToNumber(const char arg_symbol) const;
	eType DetermineType(void) const;
	void ComputeTupleCount(std::array<uint8_t, 6U>& arg_tupleCount, uint8_t& arg_jokers) const;
	bool HasNOfAKind(const int8_t arg_n, std::array<uint8_t, 6U>& arg_tupleCount, uint8_t& arg_jokers) const;

	static bool JokersEnabledGlobal;
	uint8_t cards[NumberOfCards];
	eType type;
	bool jokersEnabled;
};
