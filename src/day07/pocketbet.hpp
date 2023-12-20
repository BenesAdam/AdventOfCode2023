#pragma once

#include <string>
#include <vector>

#include "hand.hpp"

class cPocketbet
{
public:
	cPocketbet(const std::string& arg_line);
	
	static std::vector<cPocketbet> Parse(const std::string& arg_path);
	static uint32_t GetTotalWinnings(std::vector<cPocketbet>& arg_pocketbets);

	bool operator<(const cPocketbet& other) const;
	uint32_t GetBet(void) const;

private:
	cHand hand;
	uint32_t bet;
};

