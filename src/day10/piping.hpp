#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

class cPiping
{
public:
	cPiping(const std::string& arg_path);

	uint32_t StepsToMeetAnimal(void);

private:
	void FindLoop(void);
	uint16_t GetStart(void) const;
	bool FindNextPipe(uint16_t& arg_i, uint16_t& arg_j);
	bool IsNeighbourValid(const char arg_centerPiece, const char arg_neighbour, const std::pair<int8_t, int8_t>& arg_offset) const;

	void ConvertTo2D(const uint16_t arg_index, uint16_t& arg_i, uint16_t& arg_j) const;
	uint16_t ConvertToIndex(const uint16_t arg_i, const uint16_t arg_j) const;

	struct PairHash {
		template <typename T1, typename T2>
		std::size_t operator () (const std::pair<T1, T2>& p) const {
			auto h1 = std::hash<T1>{}(p.first);
			auto h2 = std::hash<T2>{}(p.second);
			return h1 ^ (h2 << 1);
		}
	};

	static const std::vector<std::pair<int8_t, int8_t>> directions;
	static const std::unordered_map<std::pair<int8_t, int8_t>, std::unordered_set<char>, PairHash> allowedNeighbours;

	std::string data;
	uint16_t size;
	std::unordered_set<uint16_t> pipes;
	std::vector<uint16_t> loop;
};

