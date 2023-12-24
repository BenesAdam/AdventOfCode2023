#pragma once

#include <string>
#include <vector>
#include <unordered_set>

#include "matrix.hpp"

class cPiping
{
public:
	cPiping(const std::string& arg_path);

	uint32_t StepsToMeetAnimal(void);
	uint32_t GetNestSize(void);

private:
	void FindLoop(void);
	uint32_t GetStart(void) const;
	bool FindNextPipe(uint16_t& arg_i, uint16_t& arg_j);
	bool IsNeighbourValid(const char arg_centerPiece, const char arg_neighbour, const std::pair<int8_t, int8_t>& arg_offset) const;
	
	void FilterOutUnusedPipes(void);

	cMatrix matrix;
	std::unordered_set<uint32_t> pipes;
	std::vector<uint32_t> loop;
};
