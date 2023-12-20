#pragma once

#include <string>
#include <list>

class cEngineSchematic
{
public:
	cEngineSchematic(const std::string& arg_path);

	uint32_t GetSumOfParts(void);
	uint32_t GetSumOfGearRatio(void);

private:
	uint8_t Get(const uint16_t arg_i, const uint16_t arg_j) const;
	uint16_t GetIndex(const uint16_t arg_i, const uint16_t arg_j) const;
	void GetIndex(const uint16_t arg_index, uint16_t& arg_i, uint16_t& arg_j) const;

	std::list<uint16_t> GetAllParts(void);
	void SearchAreaForParts(std::list<uint16_t>& arg_parts, const uint16_t arg_i, const uint16_t arg_j);
	uint16_t ScanPartNumber(const uint16_t arg_i, const uint16_t arg_j);

	uint32_t GetGearRatio(const uint16_t arg_i, const uint16_t arg_j);

	static const char BlankSpot = '.';
	static const char Gear = '*';
	static const uint8_t GearAdjacentParts = 2U;

	std::string data;
	uint16_t size;
};
