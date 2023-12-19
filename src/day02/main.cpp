#include <iostream>
#include <fstream>

#include "main.hpp"

int main()
{
	std::list<cGame> games;

	//ParseGames(games, SOURCE_DIR"/day02/test1");
	ParseGames(games, SOURCE_DIR"/day02/input");

	std::cout << "Sum of IDs: " << SumOfIdentifiers(games) << std::endl;
	std::cout << "Sum of powers: " << SumOfPower(games) << std::endl;

	return 0;
}

void ParseGames(std::list<cGame>& arg_games, const std::string& arg_path)
{
	std::ifstream file(arg_path);

	if (!file.is_open())
	{
		std::cout << "File not found." << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string line = "";
	while (!file.eof())
	{
		std::getline(file, line);
		cGame parsedGame(line);
		arg_games.push_back(parsedGame);
	}
}

uint32_t SumOfIdentifiers(const std::list<cGame>& arg_games)
{
	uint32_t sum = 0U;

	cSet configuration = { 12, 13, 14 };

	for (auto& game : arg_games)
	{
		if (game.IsPossible(configuration))
		{
			sum += game.GetIdentifier();
		}
	}

	return sum;
}

uint32_t SumOfPower(const std::list<cGame>& arg_games)
{
	uint32_t sum = 0U;

	for (auto& game : arg_games)
	{
		sum += game.GetPower();
	}

	return sum;
}
