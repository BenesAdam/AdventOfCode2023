#pragma once

#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>

class cMatrix
{
public:
	cMatrix(void);
	cMatrix(const std::string& arg_path);

	uint32_t Size(void) const;
	uint16_t Width(void) const;
	uint16_t Height(void) const;

	char Get(const uint32_t arg_index) const;
	char Get(const uint16_t arg_i, const uint16_t arg_j) const;

	void Set(const uint32_t arg_index, const char arg_value);

	void ConvertTo2D(const uint32_t arg_index, uint16_t& arg_i, uint16_t& arg_j) const;
	uint32_t ConvertToIndex(const uint16_t arg_i, const uint16_t arg_j) const;

	bool IsInBoundaries(const uint16_t arg_i, const uint16_t arg_j) const;
	void Print(void) const;
	
	static cMatrix FormUpscaledPiping(const cMatrix& arg_matrix);
	void MarkNest(const cMatrix& arg_originalMatrix, const std::vector<uint32_t> arg_loop);

	struct PairHash {
		template <typename T1, typename T2>
		std::size_t operator () (const std::pair<T1, T2>& p) const {
			auto h1 = std::hash<T1>{}(p.first);
			auto h2 = std::hash<T2>{}(p.second);
			return h1 ^ (h2 << 1);
		}
	};

	static const std::vector<std::pair<int8_t, int8_t>> Directions;
	static const std::unordered_map<std::pair<int8_t, int8_t>, std::unordered_set<char>, PairHash> AllowedNeighbours;

private:
	void SpreadVoid(void);
	void SpreadVoid(const uint32_t arg_index, std::stack<uint32_t>& arg_stack);

	std::string data;
	uint16_t width;
	uint16_t height;
};
