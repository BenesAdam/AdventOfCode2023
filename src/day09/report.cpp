#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "report.hpp"

std::list<cReport> cReport::Parse(const std::string& arg_path)
{
	std::ifstream file(arg_path);

	if (!file.is_open())
	{
		std::cout << "File is not found." << std::endl;
		exit(EXIT_FAILURE);
	}

	std::list<cReport> reports;

	std::string line;
	while (!file.eof())
	{
		std::getline(file, line);
		cReport report(line);
		reports.push_back(report);
	}

	file.close();
	return reports;
}

cReport::cReport(const std::string& arg_line) :
	history(),
	increments()
{
	int64_t number;
	std::stringstream ss(arg_line);

	while (ss >> number)
	{
		history.push_back(number);
	}

	std::vector<std::vector<int64_t>> layers;
	layers.push_back(history);
	ComputeNextLayers(layers, 1U);
	
	ComputeIncrements(layers);
}

void cReport::ComputeNextLayers(std::vector<std::vector<int64_t>>& arg_layers, const uint16_t arg_sequenceIndex) const
{
	std::vector<int64_t>& previosSequence = arg_layers[arg_sequenceIndex - 1U];
	std::vector<int64_t> sequence;

	uint16_t countNonZero = 0U;

	for (uint16_t i = 1U; i < previosSequence.size(); i++)
	{
		const int64_t difference = previosSequence[i] - previosSequence[i - 1U];
		sequence.push_back(difference);

		if (difference != 0)
		{
			countNonZero++;
		}
	}

	arg_layers.push_back(sequence);

	if (countNonZero != 0U)
	{
		ComputeNextLayers(arg_layers, arg_sequenceIndex + 1U);
	}
}

void cReport::ComputeIncrements(std::vector<std::vector<int64_t>>& layers)
{
	for (auto it = layers.rbegin(); it != layers.rend(); it++)
	{
		std::vector<int64_t>& layer = *it;
		int64_t lastValue = layer[layer.size() - 1U];
		increments.push_back(lastValue);
	}
}

int64_t cReport::SumOfExtrapolatedValues(std::list<cReport>& arg_reports)
{
	int64_t sum = 0U;

	for (auto& report : arg_reports)
	{
		sum += report.ComputeNextValue();
	}

	return sum;
}

int64_t cReport::ComputeNextValue(void)
{
	for (uint16_t i = 1U; i < increments.size(); i++)
	{
		increments[i] = increments[i - 1U] + increments[i];
	}

	int64_t value = increments[increments.size() - 1U];
	history.push_back(value);

	return value;
}
