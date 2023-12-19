#pragma once

#include <list>
#include <string>
#include "game.hpp"

void ParseGames(std::list<cGame>& arg_games, const std::string& arg_path);
uint32_t SumOfIdentifiers(const std::list<cGame>& arg_games);
