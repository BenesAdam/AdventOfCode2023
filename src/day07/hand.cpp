#include <array>

#include "hand.hpp"

const std::map<char, uint8_t> cHand::cardMapping =
{
	{ 'A', 14 },
	{ 'K', 13 },
	{ 'Q', 12 },
	{ 'J', 11 },
	{ 'T', 10 },
	{ '9', 9 },
	{ '8', 8 },
	{ '7', 7 },
	{ '6', 6 },
	{ '5', 5 },
	{ '4', 4 },
	{ '3', 3 },
	{ '2', 2 }
};

cHand::cHand(void) :
	cards{ 0U, 0U, 0U, 0U, 0U },
	type(eType::HIGH_CARD)
{
}

cHand::cHand(const std::string& arg_cards) :
	cHand()
{
	// Parse cards
	for (uint8_t i = 0U; i < cHand::NumberOfCards; i++)
	{
		const char c = arg_cards[i];
		cards[i] = cardMapping.at(c);
	}

	// Determine type
	type = GetType();
}

int8_t cHand::Compare(const cHand& other) const
{
	if (this->type != other.type)
	{
		return (this->type < other.type) ? -1 : 1;
	}

	for (uint8_t i = 0U; i < cHand::NumberOfCards; i++)
	{
		const uint8_t thisCard = this->cards[i];
		const uint8_t otherCard = other.cards[i];

		if (thisCard != otherCard)
		{
			return (thisCard < otherCard) ? -1 : 1;
		}
	}

	return 0;
}

cHand::eType cHand::GetType(void) const
{
	std::map<uint8_t, uint8_t> buckets;
	for (uint8_t card : cards)
	{
		buckets[card]++;
	}

	std::array<uint8_t, 6U> tuple = { 0U };
	for (auto cardSet : buckets)
	{
		tuple[cardSet.second]++;
	}

	if (tuple[5U] == 1U)
	{
		return eType::FIVE_OF_A_KIND;
	}

	if (tuple[4U] == 1U)
	{
		return eType::FOUR_OF_A_KIND;
	}

	if (tuple[3U] == 1U)
	{
		if (tuple[2U] == 1U)
		{
			return eType::FULL_HOUSE;
		}
		else
		{
			return eType::THREE_OF_A_KIND;
		}
	}

	if (tuple[2U] > 0U)
	{
		return (tuple[2U] == 2U) ? eType::TWO_PAIR : eType::ONE_PAIR;
	}

	return eType::HIGH_CARD;
}

//-----------------------------------------------------------------------------
// Operators
//-----------------------------------------------------------------------------
bool cHand::operator==(const cHand& other) const
{
	return Compare(other) == 0U;
}

bool cHand::operator!=(const cHand& other) const
{
	return !(*this == other);
}

bool cHand::operator<(const cHand& other) const
{
	return Compare(other) == -1;
}

bool cHand::operator<=(const cHand& other) const
{
	return Compare(other) <= 0;
}

bool cHand::operator>(const cHand& other) const
{
	return Compare(other) == 1;
}

bool cHand::operator>=(const cHand& other) const
{
	return Compare(other) >= 0;
}
