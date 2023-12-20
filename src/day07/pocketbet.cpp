#include <fstream>
#include <iostream>
#include <algorithm>

#include "pocketbet.hpp"

std::vector<cPocketbet> cPocketbet::Parse(const std::string& arg_path)
{
	std::ifstream file(arg_path);

	if (!file.is_open())
	{
		std::cout << "File is not found." << std::endl;
		exit(EXIT_FAILURE);
	}

	std::vector<cPocketbet> pocketbets;
	std::string line;
	while (!file.eof())
	{
		std::getline(file, line);
		cPocketbet pocketbet(line);
		pocketbets.push_back(pocketbet);
	}

	file.close();

	return pocketbets;
}

cPocketbet::cPocketbet(const std::string& arg_line) :
	hand(),
	bet(0U)
{
	uint16_t splitPosition = arg_line.find(' ');
	std::string strHand = arg_line.substr(0U, splitPosition);
	std::string strBet = arg_line.substr(splitPosition + 1U);

	this->hand = cHand(strHand);
	this->bet = std::stoi(strBet);
}

uint32_t cPocketbet::GetTotalWinnings(std::vector<cPocketbet>& arg_pocketbets)
{
	uint32_t result = 0U;

	std::sort(arg_pocketbets.begin(), arg_pocketbets.end(), std::less<cPocketbet>());

	for (uint16_t i = 0U; i < arg_pocketbets.size(); i++)
	{
		result += (i + 1U) * arg_pocketbets[i].GetBet();
	}

	return result;
}

bool cPocketbet::operator<(const cPocketbet& other) const
{
	return this->hand < other.hand;
}

uint32_t cPocketbet::GetBet(void) const
{
	return bet;
}
