#include <iostream>

#include "pattern.hpp"

std::list<cPattern> cPattern::ParseFile(const std::string& arg_path)
{
	std::ifstream file(arg_path);

	if (!file.is_open())
	{
		std::cout << "File is not found." << std::endl;
		exit(EXIT_FAILURE);
	}

	std::list<cPattern> patterns;

	while (!file.eof())
	{
		cPattern pattern(file);
		patterns.push_back(pattern);
	}

	file.close();

	return patterns;
}

cPattern::cPattern(void) :
	width(0U),
	height(0U),
	data()
{
}

cPattern::cPattern(std::ifstream& arg_file) :
	cPattern()
{
	std::string line;

	while (!arg_file.eof())
	{
		std::getline(arg_file, line);

		if (line == "")
		{
			break;
		}

		if (data == "")
		{
			width = line.size();
		}

		height++;
		data += line;
	}
}

uint32_t cPattern::ReflectionSummarization(std::list<cPattern>& arg_patterns)
{
	uint32_t sum = 0U;

	for (auto& pattern : arg_patterns)
	{
		sum += pattern.ReflectionSummarization();
	}

	return sum;
}

uint32_t cPattern::ReflectionSummarization(void)
{
	uint32_t sum = 0U;

	// Horizontal
	uint16_t horizontalIndex = FindHorizontalReflection();
	sum += 100U * static_cast<uint32_t>(horizontalIndex);


	// Vertical
	uint16_t verticalIndex = FindVerticalReflection();
	sum += verticalIndex;

	return sum;
}

uint16_t cPattern::FindVerticalReflection(void)
{
	cPattern rotated = GetRotated();
	return rotated.FindHorizontalReflection();
}

cPattern cPattern::GetRotated(void) const
{
	cPattern rotated;

	for (uint16_t j = 0U; j < width; j++)
	{
		for (uint16_t i = 0U; i < height; i++)
		{
			rotated.data += Get(i, j);
		}
	}

	rotated.width = height;
	rotated.height = width;

	return rotated;
}

uint16_t cPattern::FindHorizontalReflection(void)
{
	// Create vector of rows
	std::vector<std::string> rows;
	for (uint16_t i = 0U; i < height; i++)
	{
		std::string row = data.substr(i * width, width);
		rows.push_back(row);
	}

	// Get non smudged solution
	uint16_t notSmudgedSolution = FindHorizontalReflection(0U, rows, sPosition<uint16_t>(0U, 0U), UINT16_MAX);

	// Find smudge and solution with smudged data
	for (int32_t firstRowIndex = 0U; firstRowIndex < (height - 1U); firstRowIndex++)
	{
		// Find smudge
		sPosition<uint16_t> smudge = UINT16_MAX;
		static_cast<void>(FindHorizontalReflection(firstRowIndex, rows, smudge, notSmudgedSolution));

		if (smudge == UINT16_MAX)
		{
			continue;
		}

		// Correct smudge
		const char smudgeCharacter = Get(smudge);
		rows[smudge.i][smudge.j] = (smudgeCharacter == '#') ? '.' : '#';

		// Find solution with corrected smudge (that should be different than non smudged solution)
		uint16_t solution = FindHorizontalReflection(0U, rows, sPosition<uint16_t>(0U, 0U), notSmudgedSolution);
		rows[smudge.i][smudge.j] = smudgeCharacter;

		if (solution != 0U)
		{
			return solution;
		}
	}

	return 0U;
}

uint16_t cPattern::FindHorizontalReflection(const uint16_t arg_firstRowIndex, std::vector<std::string>& arg_rows, 
	sPosition<uint16_t>& arg_smudge, const uint16_t arg_notSmudgedSolution)
{
	for (int32_t firstRowIndex = arg_firstRowIndex; firstRowIndex < (height - 1U); firstRowIndex++)
	{
		uint16_t secondRowIndex = firstRowIndex + 1U;

		sPosition<uint16_t> smudgeBackup = arg_smudge;
		if (CheckHorizontalReflection(arg_rows, firstRowIndex, secondRowIndex, arg_smudge))
		{
			const bool smudgeFound = arg_smudge != UINT16_MAX;
			const uint16_t solution = firstRowIndex + 1U;
			const bool differentSolution = arg_notSmudgedSolution != solution;
			if (smudgeFound && differentSolution)
			{
				return solution;
			}
			else
			{
				arg_smudge = smudgeBackup;
			}
		}
	}

	return 0U;
}

bool cPattern::CheckHorizontalReflection(std::vector<std::string>& arg_rows, const uint16_t arg_firstRowIndex,
	const uint16_t arg_secondRowIndex, sPosition<uint16_t>& arg_smudge) const
{
	const std::string first = arg_rows[arg_firstRowIndex];
	const std::string second = arg_rows[arg_secondRowIndex];

	// Compare two rows
	if (first != second)
	{
		// Smudge already found
		if (arg_smudge != UINT16_MAX)
		{
			return false;
		}

		// Find exactly one smudge
		if (!ExactlyOneSmudge(first, second, arg_smudge))
		{
			return false;
		}

		arg_smudge.i = arg_firstRowIndex;
	}

	// Expansion is not possible
	if ((arg_firstRowIndex == 0U) || (arg_secondRowIndex == (height - 1U)))
	{
		return true;
	}

	// Expand left and right
	return CheckHorizontalReflection(arg_rows, arg_firstRowIndex - 1U, arg_secondRowIndex + 1U, arg_smudge);
}

bool cPattern::ExactlyOneSmudge(const std::string& arg_first, const std::string& arg_second, sPosition<uint16_t>& arg_smudge) const
{
	uint16_t smudgeVerticalPosition = 0U;
	bool smudgeFound = false;
	for (uint16_t j = 0U; j < arg_first.size(); j++)
	{
		const bool isSmudge = arg_first[j] != arg_second[j];
		if (isSmudge && smudgeFound)
		{
			return false;
		}

		if (isSmudge)
		{
			smudgeVerticalPosition = j;
			smudgeFound = true;
		}
	}

	arg_smudge.j = smudgeVerticalPosition;

	return true;
}

sPosition<uint16_t> cPattern::GetPosition(const uint32_t arg_index) const
{
	sPosition<uint16_t> position;

	position.i = arg_index / width;
	position.j = arg_index % width;

	return position;
}

uint32_t cPattern::GetIndex(const sPosition<uint16_t>& arg_position) const
{
	return GetIndex(arg_position.i, arg_position.j);
}

uint32_t cPattern::GetIndex(const uint32_t arg_i, const uint32_t arg_j) const
{
	return (arg_i * width) + arg_j;
}

char cPattern::Get(const uint32_t arg_index) const
{
	return data[arg_index];
}

char cPattern::Get(const sPosition<uint16_t>& arg_position) const
{
	return Get(arg_position.i, arg_position.j);
}

char cPattern::Get(const uint32_t arg_i, const uint32_t arg_j) const
{
	return Get(GetIndex(arg_i, arg_j));
}
