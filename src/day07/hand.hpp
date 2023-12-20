#pragma once

#include <string>
#include <map>

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

	static const std::map<char, uint8_t> cardMapping;
	static const uint8_t NumberOfCards = 5U;

	// operators
	bool operator==(const cHand& other) const;
	bool operator!=(const cHand& other) const;
	bool operator<(const cHand& other) const;
	bool operator<=(const cHand& other) const;
	bool operator>(const cHand& other) const;
	bool operator>=(const cHand& other) const;

private:
	eType GetType(void) const;

	uint8_t cards[NumberOfCards];
	eType type;
};
