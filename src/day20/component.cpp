#include <iostream>
#include <regex>
#include <sstream>
#include <fstream>

#include "component.hpp"
#include "flip_flop.hpp"
#include "conjuction.hpp"
#include "broadcaster.hpp"
#include "dummy_component.hpp"

cComponent::cComponent(void) :
	name(),
	neighboursByName(),
	inputNeighbours(),
	outputNeighbours()
{
}

cComponent::cComponent(const std::string arg_name) :
	name(arg_name),
	neighboursByName(),
	inputNeighbours(),
	outputNeighbours()
{
}

cComponent::cComponent(const std::string arg_name, std::list<std::string> arg_neighboursByName) :
	name(arg_name),
	neighboursByName(arg_neighboursByName),
	inputNeighbours(),
	outputNeighbours()
{
}

std::map<std::string, cComponent*> cComponent::ParseFile(const std::string arg_path)
{
	std::map<std::string, cComponent*> result;

	std::ifstream file(arg_path);
	if (!file.is_open())
	{
		std::cout << "File is not found." << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string line;
	while (!file.eof())
	{
		std::getline(file, line);
		cComponent* component = cComponent::ParseLine(line);
		result.emplace(component->GetName(), component);
	}

	file.close();

	return result;
}

cComponent* cComponent::ParseLine(const std::string arg_line)
{
	std::smatch m;
	std::regex r("(.*) -> (.*)");
	std::regex_search(arg_line, m, r);

	const std::string name = m[1];
	std::list<std::string> neighbours;
	ParseNeighbours(neighbours, m[2]);


	if (arg_line.find('%') != std::string::npos)
	{
		return new cFlipFlop(name.substr(1U), neighbours);
	}
	else if (arg_line.find('&') != std::string::npos)
	{
		return new cConjunction(name.substr(1U), neighbours);
	}
	else
	{
		return new cBroadcaster(name, neighbours);
	}
}

void cComponent::ParseNeighbours(std::list<std::string>& arg_neighbours, const std::string arg_neighboursStr)
{
	std::string str = arg_neighboursStr;
	str.erase(remove(str.begin(), str.end(), ' '), str.end());

	std::stringstream ss(str);
	std::string name;
	while (std::getline(ss, name, ','))
	{
		arg_neighbours.push_back(name);
	}
}

void cComponent::Init(std::map<std::string, cComponent*>& arg_components)
{
	for (auto& neighbourName : neighboursByName)
	{
		if (arg_components.find(neighbourName) == arg_components.end())
		{
			cComponent* dummyComponent = new cDummyComponent(neighbourName);
			arg_components.emplace(neighbourName, dummyComponent);
		}

		cComponent* neighbour = arg_components[neighbourName];
		outputNeighbours.insert(neighbour);
		neighbour->RegisterInputNeighbour(this);
	}
}

void cComponent::RegisterInputNeighbour(cComponent* arg_component)
{
	inputNeighbours.insert(arg_component);
	RegisterInputNeighbourExtra(arg_component);
}

std::set<cComponent*> cComponent::GetInputNeighbours(void) const
{
	return inputNeighbours;
}

void cComponent::Reset(void)
{
}

void cComponent::Print(void) const
{
	// Name
	std::cout << GetPrefix() << name << " ->";

	// Output neighbours
	for (auto& neighbour : outputNeighbours)
	{
		std::cout << " " << neighbour->GetName();
	}

	// Input neighbours
	std::cout << " (";
	for (auto& neighbour : inputNeighbours)
	{
		std::cout << " " << neighbour->GetName();
	}

	std::cout << " )" << std::endl;
}

std::string cComponent::GetName(void) const
{
	return name;
}

void cComponent::RegisterInputNeighbourExtra(cComponent* arg_component)
{
}

cComponent::sPulse::sPulse(const eSignal arg_signal, cComponent* arg_from, cComponent* arg_to) :
	signal(arg_signal),
	from(arg_from),
	to(arg_to)
{
}
