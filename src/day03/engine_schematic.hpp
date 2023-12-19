#pragma once

#include <string>
#include <list>

class cEngineSchematic
{
public:
	cEngineSchematic(const std::string& arg_path);

	uint32_t GetSumOfParts(void);
	void Print(void) const;

private:
	uint8_t Get(const uint16_t arg_i, const uint16_t arg_j) const;
	uint16_t GetIndex(const uint16_t arg_i, const uint16_t arg_j) const;
	void GetIndex(const uint16_t arg_index, uint16_t& arg_i, uint16_t& arg_j) const;

	std::list<uint16_t> GetParts(void);
	void AskNeighboursForParts(std::list<uint16_t>& arg_parts, const uint16_t arg_i, const uint16_t arg_j);
	uint16_t ScanPartNumber(const uint16_t arg_i, const uint16_t arg_j, const bool arg_pickAndRemove);

	static const char BlankSpot = '.';

	std::string data;
	uint16_t size;
};
