#pragma once

#include <string>
#include <vector>

#include "position.hpp"

class cPlatform
{
public:
	enum class eTiltDirection
	{
		NORTH, WEST, SOUTH, EAST,
	};

	cPlatform(const std::string& arg_path);

	void Print(void) const;
	uint32_t TotalNorthLoadPart1(void);
	uint32_t TotalNorthLoadPart2(const uint64_t arg_cyclesCount);

private:
	uint32_t TotalNorthLoad(void);
	void OneCycle(void);

	void Tilt(const cPlatform::eTiltDirection arg_dir);
	void Tilt(const cPlatform::eTiltDirection arg_dir, const uint16_t arg_i, const uint16_t arg_j);
	bool IsOnEdge(const cPlatform::eTiltDirection arg_dir, const uint16_t arg_i, const uint16_t arg_j) const;
	uint32_t GetNextIndex(const cPlatform::eTiltDirection arg_dir, const uint16_t arg_i, const uint16_t arg_j) const;

	uint32_t GetIndex(const uint16_t arg_i, const uint16_t arg_j) const;
	sPosition<uint16_t> GetPosition(const uint32_t arg_index) const;
	uint16_t NumberOfRoundedRocks(const uint16_t arg_i) const;

	uint16_t width;
	uint16_t height;
	std::string data;
};
