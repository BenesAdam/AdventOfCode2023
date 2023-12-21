#include <map>

#include "hand.hpp"

bool cHand::JokersEnabledGlobal = false;

void cHand::EnableJokers(void)
{
	JokersEnabledGlobal = true;
}

void cHand::DisableJokers(void)
{
	JokersEnabledGlobal = false;
}

cHand::cHand(void) :
	cards{ 0U, 0U, 0U, 0U, 0U },
	type(eType::HIGH_CARD),
	jokersEnabled(cHand::JokersEnabledGlobal)
{
}

cHand::cHand(const std::string& arg_cards) :
	cards{ 0U, 0U, 0U, 0U, 0U },
	type(eType::HIGH_CARD),
	jokersEnabled(cHand::JokersEnabledGlobal)
{
	// Parse cards
	for (uint8_t i = 0U; i < cHand::NumberOfCards; i++)
	{
		const char c = arg_cards[i];
		cards[i] = ConvertSymbolToNumber(c);
	}

	// Determine type
	type = DetermineType();
}

uint8_t cHand::ConvertSymbolToNumber(const char arg_symbol) const
{
	static const std::map<char, uint8_t> cardMapping =
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
		{ '2', 2 },
	};
	
	uint8_t result = cardMapping.at(arg_symbol);

	if ((arg_symbol == 'J') && (jokersEnabled))
	{
		result = 1U;
	}

	return result;
}

cHand::eType cHand::DetermineType(void) const
{
	std::array<uint8_t, 6U> tupleCount = { 0U };
	uint8_t jokers = 0U;

	ComputeTupleCount(tupleCount, jokers);

	if ((HasNOfAKind(5, tupleCount, jokers)) || (HasNOfAKind(0, tupleCount, jokers)))
	{
		return eType::FIVE_OF_A_KIND;
	}

	if (HasNOfAKind(4, tupleCount, jokers))
	{
		return eType::FOUR_OF_A_KIND;
	}

	if (HasNOfAKind(3, tupleCount, jokers))
	{
		if (HasNOfAKind(2, tupleCount, jokers))
		{
			return eType::FULL_HOUSE;
		}
		else
		{
			return eType::THREE_OF_A_KIND;
		}
	}

	if (HasNOfAKind(2, tupleCount, jokers))
	{
		if (HasNOfAKind(2, tupleCount, jokers))
		{
			return eType::TWO_PAIR;
		}
		else
		{
			return eType::ONE_PAIR;
		}
	}

	return eType::HIGH_CARD;
}

void cHand::ComputeTupleCount(std::array<uint8_t, 6U>& arg_tupleCount, uint8_t& arg_jokers) const
{
	// Compute number of cards of each kind and number of jokers
	std::map<uint8_t, uint8_t> buckets;
	for (uint8_t card : cards)
	{
		if (jokersEnabled)
		{
			if (card != ConvertSymbolToNumber('J'))
			{
				buckets[card]++;
			}
			else
			{
				arg_jokers++;
			}
		}
		else
		{
			buckets[card]++;
		}
	}

	// Compute number of tuple for each kind
	for (auto cardSet : buckets)
	{
		arg_tupleCount[cardSet.second]++;
	}

	// Special case for all jokers
	if ((jokersEnabled) && (buckets.size() == 0U))
	{
		arg_tupleCount[0]++;
	}
}

bool cHand::HasNOfAKind(const int8_t arg_n, std::array<uint8_t, 6U>& arg_tupleCount, uint8_t& arg_jokers) const
{
	for (int8_t n = arg_n; n >= 0; n--)
	{
		const bool hasDesiredTuple = arg_tupleCount[n] >= 1;
		const uint8_t jokersNeeded = arg_n - n;
		const bool hasEnoughJokers = arg_jokers >= jokersNeeded;
		if (hasDesiredTuple && hasEnoughJokers)
		{
			arg_tupleCount[n]--;
			arg_jokers -= jokersNeeded;

			return true;
		}
	}

	return false;
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
